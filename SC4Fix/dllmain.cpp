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

#include <Windows.h>
#include <stdio.h>

#include "DLLUnloadPreempt.h"
#include "PuzzlePieceTE.h"

uint16_t nGameVersion = 0;

void DetermineGameVersion(void) {
	TCHAR szVersionFile[MAX_PATH];
	GetModuleFileName(NULL, szVersionFile, MAX_PATH);

	// http://stackoverflow.com/a/940743
	DWORD  verHandle = NULL;
	UINT   size      = 0;
	LPBYTE lpBuffer  = NULL;
	DWORD  verSize   = GetFileVersionInfoSize(szVersionFile, &verHandle);

	if (verSize > 0) {
		LPSTR verData = new char[verSize];
		if (GetFileVersionInfo(szVersionFile, verHandle, verSize, verData)
			&& VerQueryValue(verData, "\\", (VOID FAR* FAR*)&lpBuffer, &size)
			&& size > 0) {
			VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
			if (verInfo->dwSignature = 0xfeef04bd) {
				uint16_t wMajorVer = (verInfo->dwFileVersionMS >> 16) & 0xFFFF;
				uint16_t wMinorVer = verInfo->dwFileVersionMS & 0xFFFF;
				uint16_t wRevision = (verInfo->dwFileVersionLS >> 16) & 0xFFFF;
				uint16_t wBuildNum = verInfo->dwFileVersionLS & 0xFFFF;

				// 1.1.x.x
				if (wMajorVer == 1 && wMinorVer == 1) {
					nGameVersion = wRevision;
				}
				else {
					nGameVersion = 0;
				}
			}
		}

		delete[] verData;
	}

	// Fall back to a less accurate detection mechanism
	if (nGameVersion == 0) {
		uint8_t uSentinel = *(uint8_t*)0x6E5000;

		switch (uSentinel) {
		case 0x8B: nGameVersion = 610; break; // Can't distinguish from 613
		case 0xFF: nGameVersion = 638; break;
		case 0x24: nGameVersion = 640; break;
		case 0x0F: nGameVersion = 641; break;
		default:   nGameVersion = 0;  break;
		}
	}
}

uint16_t GetGameVersion(void) {
	return nGameVersion;
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

//----------------------------------------------------------
// NOTE: All unnamed subroutines are based on their
// addresses in patch 640.
//----------------------------------------------------------
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		DetermineGameVersion();

		uint16_t wVersion = GetGameVersion();
		if (wVersion == 610 || wVersion == 613) {
			HandleVersion610Or613();
			return FALSE;
		}
		else if (wVersion == 638) {
			HandleVersion638();
		}
		else if (wVersion != 640 && wVersion != 641) {
			HandleUnknownVersion();
		}

		CPatcher::UnprotectAll();
		DLLUnloadPreempt::InstallPatch();
		PuzzlePieceTE::InstallPatch();

		MessageBoxA(NULL, "SC4Fix loaded", "SC4Fix", NULL);
	}

	return TRUE;
}

