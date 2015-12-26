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
#include "patcher.h"

#include <Windows.h>
#include <stdio.h>
#include <stdint.h>

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

//----------------------------------------------------------
// NOTE: All unnamed subroutines are based on their
// addresses in patch 640.
//----------------------------------------------------------
BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);
		CPatcher::UnprotectAll();

		DLLUnloadPreempt::InstallPatch();
		PuzzlePieceTE::InstallPatch();

		MessageBoxA(NULL, "SC4Fix loaded", "SC4Fix", NULL);
	}

	return TRUE;
}

