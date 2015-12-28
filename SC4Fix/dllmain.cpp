/*
   Project: SC4Fix Patches for SimCity 4
   File: dllmain.cpp

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

#define WIN32_LEAN_AND_MEAN
#include "dllmain.h"
#include "patcher.h"
#include "version.h"

#include <Windows.h>
#include <stdio.h>

#include "DLLUnloadPreempt.h"
#include "PuzzlePieceTE.h"
#include "TitleBarMod.h"

// This should never be modified or else you'll create
// conflicts between versions.
#define MUTEX_NAME "SC4Fix_{FA65A963-9315-4A2F-ADBB-4A2F36E056F5}"

HANDLE hMutex;
BOOL ReserveInstance(void) {
	hMutex = CreateMutexA(NULL, FALSE, MUTEX_NAME);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		return FALSE;
	}

	return TRUE;
}

void HandleConflictingInstances(HMODULE hModule) {
	const char* szFmt = "There appear to be multiple instances of SC4Fix installed in your "
						"plugins folder.\n"
						"\n"
						"This copy of SC4Fix will abort loading in order to avoid damaging "
						"and destabilizing your game. It is still recommended that you "
						"remove this copy and other conflicting copies of SC4Fix. Once "
						"you have done that, this message will no longer appear.\n"
						"\n"
						"This duplicate copy of SC4Fix can be located at this path:\n"
						"%s";

	char* szPath = new char[MAX_PATH];
	GetModuleFileNameA(hModule, szPath, MAX_PATH);

	const int nMessageLen = strlen(szFmt) + MAX_PATH;
	char* szMsg = new char[nMessageLen];
	sprintf_s(szMsg, nMessageLen, szFmt, szPath);

	MessageBoxA(NULL, szMsg, "SC4Fix: Conflicting DLLs", MB_OK | MB_ICONEXCLAMATION);

	delete[] szPath;
	delete[] szMsg;
}

//----------------------------------------------------------
// NOTE: All unnamed subroutines are based on their
// addresses in patch 640.
//----------------------------------------------------------
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		if (!ReserveInstance()) {
			HandleConflictingInstances(hModule);
			return FALSE;
		}

		DetermineGameVersion();

		uint16_t wVersion = GetGameVersion();
		if (wVersion == 610 || wVersion == 613) {
			HandleVersion610Or613();
			return FALSE;
		}
		else if (wVersion == 638) {
			HandleVersion638();
			return FALSE;
		}
		else if (wVersion != 640 && wVersion != 641) {
			HandleUnknownVersion();
			return FALSE;
		}

		CPatcher::UnprotectAll();
		DLLUnloadPreempt::InstallPatch();
		PuzzlePieceTE::InstallPatch();
		TitleBarMod::InstallPatch();
	}

	return TRUE;
}

