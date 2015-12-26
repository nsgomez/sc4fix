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

/*
			| 610 | 613 | 638 | 640 | 641
	--------+-----------------------------
	0x65EE0C| x23 | x23 | x03 | xD9 | xDD
	0x65EE40| x00 | x00 | x22 | x63 | x8B
	0x65EE6C| x08 | x08 | x0C | x75 | x5B
*/
void DetermineGameVersion(void) {
	uint8_t uSentinel = *(uint8_t*)0x65EE0C;

	switch (uSentinel) {
	case 0x00: nGameVersion = 610; break;
	case 0x22: nGameVersion = 638; break;
	case 0x63: nGameVersion = 640; break;
	case 0x8B: nGameVersion = 641; break;
	default:   nGameVersion = 0;  break;
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

		switch (GetGameVersion()) {
		case 610:
		case 613: // 613 seems identical to 610 in terms of code
			HandleVersion610Or613();
			return FALSE;

		case 638:
			HandleVersion638();
			return FALSE;

		case 640:
		case 641:
			break;

		case 0:
		default:
			HandleUnknownVersion();
			return FALSE;
		}

		CPatcher::UnprotectAll();

		DLLUnloadPreempt::InstallPatch();
		PuzzlePieceTE::InstallPatch();

		MessageBoxA(NULL, "SC4Fix loaded", "SC4Fix", NULL);
	}

	return TRUE;
}

