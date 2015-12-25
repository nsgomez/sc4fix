/*
   Project: SC4Fix Patches for SimCity 4
   File: exceptions.cpp

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

#include "exceptions.h"
#include <Psapi.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int UnsignedComparator(const void * a, const void * b) {
	return *(uint32_t*)a - *(uint32_t*)b;
}

void StoreCrashLogText(_EXCEPTION_POINTERS* exc_inf) {
	static char filename[64];
	static int crashID = 1;
	PCONTEXT cxt = exc_inf->ContextRecord;

	sprintf_s(filename, "%d_%d.txt", GetTickCount(), crashID++);
	FILE* file = fopen(filename, "w");

	fprintf_s(file, "Address: %08X error %08X\nEAX %08X EBX %08X ECX %08X EDX %08X\nEBP %08X ESP %08X ESI %08X EDI %08X\nStack: \n", cxt->Eip, exc_inf->ExceptionRecord->ExceptionCode, cxt->Eax, cxt->Ebx, cxt->Ecx, cxt->Edx, cxt->Ebp, cxt->Esp, cxt->Esi, cxt->Edi);

	uint32_t* stack = (uint32_t*)cxt->Esp;

	for (int i = 0; i < 100; i++) {
		if (IsBadReadPtr(&stack[i], sizeof(uint32_t))) {
			fprintf_s(file, "Bad stack address %08X\n", &stack[i]);
			break;
		}
		else {
			fprintf_s(file, "%08X\n", stack[i]);
		}
	}

	HMODULE hModules[512];
	DWORD cbNeeded;

	if (EnumProcessModules(GetCurrentProcess(), hModules, sizeof(hModules), &cbNeeded)) {
		qsort(hModules, cbNeeded / sizeof(HMODULE), sizeof(HMODULE), UnsignedComparator);

		for (int i = 0; i < (int)(cbNeeded / sizeof(HMODULE)); i++) {
			char szModName[MAX_PATH];
			MODULEINFO modInfo;

			if (GetModuleFileNameExA(GetCurrentProcess(), hModules[i], szModName, sizeof(szModName)) &&
				GetModuleInformation(GetCurrentProcess(), hModules[i], &modInfo, sizeof(MODULEINFO))) {

				fprintf_s(file, "%08X S %08X N %s\n", (uint32_t)hModules[i], modInfo.SizeOfImage, szModName);
			}
			else {
				fprintf_s(file, "%08X - unknown module.\n", (uint32_t)hModules[i]);
			}
		}
	}

	fprintf_s(file, "\n");
}

LONG WINAPI ExceptionHandlerFunc(_EXCEPTION_POINTERS* exc_inf) {
	StoreCrashLogText(exc_inf);
	MessageBoxA(NULL, "An error occurred.\nReport this in the SC4Fix development thread.", "Unexpected Error", MB_OK | MB_ICONERROR);

	return EXCEPTION_EXECUTE_HANDLER;
}