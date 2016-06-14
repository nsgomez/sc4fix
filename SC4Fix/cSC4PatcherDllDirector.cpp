/*
   Project: SC4Fix Patches for SimCity 4
   File: cSC4PatcherDllDirector.cpp

   Copyright (c) 2015 Nelson Gomez (simmaster07)

   Licensed under the MIT License. A copy of the License is available in
   LICENSE or at:

       http://opensource.org/licenses/MIT

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
   THE SOFTWARE.
*/

#include <stdio.h>
#include <cIGZApp.h>
#include <cIGZFrameWork.h>
#include <cIGZSystemService.h>
#include <cISC4App.h>
#include <cISC4FeatureManager.h>
#include <cRZAutoRefCount.h>
#include <cRZCOMDllDirector.h>
#include <cRZSysServPtr.h>

#include "cIRZGamePatcher.h"
#include "cISC4Patcher.h"
#include "cSC4GamePatcher640.h"
#include "cSC4GamePatcher641.h"
#include "version.h"

// This must be unique for every plugin. Generate a random 32-bit integer and use it.
// DO NOT REUSE DIRECTOR IDS EVER.
static const uint32_t kPatcherCOMDirectorID = 0x59d87a03;
static const uint32_t kPatcherServiceID = 0x0;
static const uint32_t kPatcherVersion = 0;

static const uint32_t kGZIID_cIGZSystemService = 0x287fb697;
static const uint32_t kGZIID_cISC4App = 0x26ce01c0;
static const uint32_t kGZIID_cISC4Patcher = 0x9a5d0ee6;

// This is a bare-bones example of a class that can be loaded into the game.
// Any DLLs you make should be derived off this example, as the other example
// (cGZExampleDllDirector) overrides basically every method just to demonstrate
// the functionality for no useful reason.
class cSC4PatcherDllDirector : public cRZCOMDllDirector, public cIGZSystemService, public cISC4Patcher
{
	public:
		cSC4PatcherDllDirector() {
			dwServiceID = kPatcherServiceID;
			bRunning = false;
		}

		uint32_t AddRef() {
			return cRZCOMDllDirector::AddRef();
		}

		uint32_t Release() {
			return cRZCOMDllDirector::Release();
		}

		bool QueryInterface(uint32_t riid, void** ppvObj) {
			if (riid == kGZIID_cIGZSystemService) {
				*ppvObj = static_cast<cIGZSystemService*>(this);
				AddRef();
				return true;
			}
			else {
				return cRZCOMDllDirector::QueryInterface(riid, ppvObj);
			}
		}

		virtual ~cSC4PatcherDllDirector() {
			// You could do something here, but everything except the OS is
			// dead by the time you get here.
		}

	public:
		uint32_t GetDirectorID() const {
			return kPatcherCOMDirectorID;
		}

		bool OnStart(cIGZCOM* pCOM) {
			// This automatically gets called by the framework after loading
			// the library.
			//
			// Register for callbacks so we can get PreFrameWorkInit,
			// PreAppInit, and other callbacks.
			RZGetFrameWork()->AddHook(static_cast<cIGZFrameWorkHooks*>(this));
			return true;
		}

		bool PreAppInit(void) {
			if (!RunningSupportedVersion()) {
				return false;
			}
			else if (OtherInstanceRunning()) {
				return false;
			}

			// Registering ourselves as a service acts as a mutex of sorts.
			RZGetFrameWork()->AddSystemService(this);

			// Implement the patches.
			switch (GetGameVersion()) {
				case 640:
					pGamePatcher = new cSC4GamePatcher640();
					break;
				
				case 641:
					pGamePatcher = new cSC4GamePatcher641();
					break;
				
				default:
					break;
			}

			pGamePatcher->AddRef();
			return true;
		}

	public:
		uint32_t GetServiceID(void) {
			return dwServiceID;
		}

		cIGZSystemService* SetServiceID(uint32_t dwServiceID) {
			this->dwServiceID = dwServiceID;
			return this;
		}

		int32_t GetServicePriority(void) {
			return 0;
		}

		bool IsServiceRunning(void) {
			return bRunning;
		}

		cIGZSystemService* SetServiceRunning(bool bRunning) {
			this->bRunning = bRunning;
			return this;
		}

		bool Init(void) {
			return true;
		}

		bool Shutdown(void) {
			return true;
		}

		bool OnTick(void) {
			return false;
		}

		bool OnIdle(void) {
			return false;
		}
	
	public:
		uint32_t GetVersion(void) {
			return kPatcherVersion;
		}

		bool TriggerUpdateWarning(void) {
			const char* szMsg = "SC4Fix has encountered a version conflict.\n"
				"\n"
				"Multiple versions of SC4Fix are currently installed, but an older version "
				"was loaded before another newer version that you have installed.\n"
				"\n"
				"The outdated DLL is located at the following path:\n"
				"%s\n"
				"\n"
				"This DLL should be removed to allow the newer version to load."
				"SimCity 4 will continue to load with the old version's patches,"
				"but the updated version will stop loading.";

			char szPath[MAX_PATH];
			GetModuleFileNameA(NULL, szPath, MAX_PATH);

			cRZBaseString szFormattedMsg;
			szFormattedMsg.Sprintf(szMsg, szPath);

			HRESULT hr = MessageBoxA(NULL, szFormattedMsg.ToChar(),
				"SC4Fix: Version Conflict", MB_OK | MB_ICONEXCLAMATION);
			
			if (!SUCCEEDED(hr)) {
				return false;
			}

			return true;
		}

		bool UnregisterPatcher(void) {
			pGamePatcher->Release();
			pGamePatcher = nullptr;
		}

	protected:
		bool OtherInstanceRunning(void) {
			cRZSysServPtr<cISC4Patcher, kGZIID_cISC4Patcher, kPatcherServiceID> pPatcher;
			if (pPatcher) {
				if (pPatcher->GetVersion() < this->GetVersion()) {
					pPatcher->TriggerUpdateWarning();
				}

				return true;
			}

			if (NonMutexedInstanceExists()) {
				HandleNonMutexedInstance();
				return true;
			}

			return false;
		}

		bool NonMutexedInstanceExists(void) {
			// Check if the DLL unload preempt is already in place
			uint32_t dwAddress = NULL;
			switch (GetGameVersion()) {
				case 640:
					dwAddress = 0x96D935;
					break;

				case 641:
					dwAddress = 0x96DA1D;
					break;

				default:
					return false;
			}

			// We know the TE fix is in place if the code at this
			// address already has MOV instructions.
			if (*(uint8_t*)dwAddress == 0xE9) {
				return true;
			}

			return false;
		}

		bool RunningSupportedVersion(void) {
			DetermineGameVersion();

			uint16_t wVersion = GetGameVersion();
			switch (wVersion) {
				case 610:
				case 613:
					HandleVersion610Or613();
					return false;
				
				case 638:
					HandleVersion638();
					return false;

				case 640:
				case 641:
					return true;

				default:
					HandleUnknownVersion();
					return false;
			}
		}

	protected:
		void HandleNonMutexedInstance(void) {
			const char* szMsg = "SC4Fix has encountered a version conflict.\n"
				"\n"
				"Multiple versions of SC4Fix are currently installed, but an older version "
				"was loaded before another newer version that you have installed.\n"
				"\n"
				"The outdated DLL is too old to locate automatically (older than r4),"
				"and was likely manually installed in the Plugins folder.\n"
				"\n"
				"This DLL should be removed to allow the newer version to load."
				"SimCity 4 will continue to load with the old version's patches,"
				"but the updated version will stop loading.";

			MessageBoxA(NULL, szMsg, "SC4Fix: Version Conflict", MB_OK | MB_ICONEXCLAMATION);
		}

		void HandleVersion610Or613(void) {
			const char* szMsg = "You appear to be running an unpatched version of SimCity 4 "
				"(version 610 or 613).\n"
				"\n"
				"SC4Fix only supports versions 640 (retail) and 641 (digital distribution) "
				"of SimCity 4. You can update your game to version 638, and then update to "
				"version 640 after that, to take advantage of this mod.\n"
				"\n"
				"Update 638 can be downloaded here:\n"
				"http://tinyurl.com/SC4638\n"
				"\n"
				"Update 640 can be downloaded here:\n"
				"http://tinyurl.com/SC4640 (Buildings Update)\n"
				"\n"
				"SC4Fix will not load further. Your game will continue to launch.";

			MessageBoxA(NULL, szMsg, "SC4Fix: Unsupported Game Version", MB_OK | MB_ICONEXCLAMATION);
		}

		void HandleVersion638(void) {
			const char* szMsg = "You appear to be running an unpatched version of SimCity 4 "
				"(version 638).\n"
				"\n"
				"SC4Fix only supports versions 640 (retail) and 641 (digital distribution) "
				"of SimCity 4. You can update your game by using the link below and "
				"downloading the Buildings Update.\n"
				"\n"
				"Update 640 can be downloaded here:\n"
				"http://tinyurl.com/SC4640\n"
				"\n"
				"SC4Fix will not load further. Your game will continue to launch.";

			MessageBoxA(NULL, szMsg, "SC4Fix: Unsupported Game Version", MB_OK | MB_ICONEXCLAMATION);
		}

		void HandleUnknownVersion(void) {
			const char* szMsg = "SC4Fix could not identify your version of SimCity 4.\n"
				"\n"
				"You may be running a vanilla version of SimCity, without the Rush Hour "
				"expansion pack. If this is the case, it is strongly recommended that "
				"you buy SimCity 4 Deluxe or the Rush Hour expansion separately, as "
				"SC4Fix not only does not support the vanilla game, but many other "
				"modifications will require a copy with Rush Hour as well.\n"
				"\n"
				"SC4Fix will not load further. Your game will continue to launch.";

			MessageBoxA(NULL, szMsg, "SC4Fix: Unknown Game Version", MB_OK | MB_ICONEXCLAMATION);
		}

	protected:
		uint32_t dwServiceID;
		bool bRunning;

		cIRZGamePatcher* pGamePatcher;
};

cRZCOMDllDirector* RZGetCOMDllDirector() {
	static cSC4PatcherDllDirector sDirector;
	return &sDirector;
}