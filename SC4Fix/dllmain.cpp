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

#include <stdio.h>

#include "dllmain.h"
#include "patcher.h"
#include "version.h"

#include "DLLUnloadPreempt.h"
#include "PropPoxVaccine.h"
#include "PuzzlePieceTE.h"

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
		}
		else if (wVersion == 638) {
			HandleVersion638();
		}
		else if (wVersion != 640 && wVersion != 641) {
			HandleUnknownVersion();
		}
		else {
			CPatcher::UnprotectAll();
			DLLUnloadPreempt::InstallPatch();
			PuzzlePieceTE::InstallPatch();
			PropPoxVaccine::InstallPatch();

			FILE* fp = fopen("SC4Fix.log", "w");
			if (fp != NULL)
			{
				fputs("Loaded SC4Fix version " SC4FIX_RELEASE_VER "\r\n", fp);
				fprintf(fp, "Detected game version %u\r\n", wVersion);
				fclose(fp);
			}

			return TRUE;
		}
	}

	return FALSE;
}

