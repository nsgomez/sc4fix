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
#include "exceptions.h"
#include "patcher.h"

#include <Windows.h>
#include <stdio.h>
#include <stdint.h>

//--- FIX CRASH WHEN HOVERING PUZZLE PIECES OVER LE LOTS ---
// Seems to be a null dereference issue though I don't have
// many details as to what exactly causes it.
//----------------------------------------------------------
void __declspec(naked) Hook_Sub96D8E9(void) {
	static void* pUnknown;

	_asm mov dword ptr ds:[esi+4ch], ecx
	_asm mov pUnknown, eax
	_asm pushad

	if (pUnknown == NULL) {
		_asm popad
		ASMJMP(96D93Bh);
	}

	_asm popad
	_asm inc dword ptr ds:[eax+4]
	ASMJMP(96D93Bh);
}

void __declspec(naked) Hook_Sub65EBA0(void) {
	static void* pUnknown;

	_asm mov dword ptr ds:[eax], ebx
	_asm mov pUnknown,esi
	_asm pushad

	if (pUnknown == NULL) {
		_asm popad
		ASMJMP(65EC86h);
	}

	_asm popad
	_asm mov ecx,dword ptr ds:[esi+18h]
	ASMJMP(65EC63h);
}

// This is especially weird: whatever was at ecx is
// tested to see if it's null, and if it is, it jumps
// to some cleanup code which dereferences it anyway.
void __declspec(naked) Hook_Sub65EBA0_Pt2(void) {
	static void* pUnknown;

	_asm mov pUnknown, ecx
	_asm pushad

	if (pUnknown == NULL) {
		_asm popad
		_asm xor edx,edx
	}
	else {
		_asm popad
		_asm mov edx,dword ptr ds:[ecx+4]
	}

	_asm fstp st
	ASMJMP(65EC8Bh);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(hModule);

		CPatcher::UnprotectAll();
		CPatcher::InstallHook(0x96D935, Hook_Sub96D8E9);
		CPatcher::InstallHook(0x65EC5E, Hook_Sub65EBA0);
		CPatcher::InstallHook(0x65EC86, Hook_Sub65EBA0_Pt2);

		//--- DISABLE LIBRARY UNLOADING IN SC4 ---------------------
		// Replaces a call in cGZCOMLibrary::Free to FreeLibrary
		// with a no-op. SC4 won't know that any nonstandard
		// DLLs are loaded, but they'll remain loaded in memory
		// nonetheless.
		//----------------------------------------------------------
		memset((void*)0x87B5A3, 0x90, 5);

		MessageBoxA(NULL, "SC4Fix loaded", "SC4Fix", NULL);
	}

	return TRUE;
}

