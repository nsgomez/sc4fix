/*
   Project: SC4Fix Patches for SimCity 4
   File: singleinstance.cpp

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

#include "singleinstance.h"
#include <Psapi.h>
#include <stdio.h>

HANDLE hMutex;
BOOL NonMutexedInstanceExists(void) {
	// Check if the DLL unload preempt is already in place
	uint32_t dwAddress = NULL;
	switch (GetGameVersion()) {
	case 640:
		dwAddress = 0x87B5A3;
		break;

	case 641:
		dwAddress = 0x87B3D1;
		break;

	default:
		return FALSE;
	}

	// We know DLL unloading is preempted if the code at
	// this address is already filled with NOP instructions.
	if (*(uint8_t*)dwAddress == 0x90) {
		return TRUE;
	}

	return FALSE;
}

BOOL ReserveInstance(void) {
	hMutex = CreateMutexA(NULL, FALSE, MUTEX_NAME);
	if (GetLastError() == ERROR_ALREADY_EXISTS) {
		return FALSE;
	}

	return TRUE;
}

BOOL ReleaseInstance(void) {
	if (hMutex != NULL) {
		return ReleaseMutex(hMutex);
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

	const int nMessageLen = strlen(szFmt) + MAX_PATH;
	char* szMsg = new char[nMessageLen];

	if (hModule != NULL) {
		char* szPath = new char[MAX_PATH];
		GetModuleFileNameA(hModule, szPath, MAX_PATH);

		sprintf_s(szMsg, nMessageLen, szFmt, szPath);
		delete[] szPath;
	}
	else {
		sprintf_s(szMsg, nMessageLen, szFmt,
			"<SC4Fix could not automatically determine where the duplicate copy is.>");
	}

	MessageBoxA(NULL, szMsg, "SC4Fix: Conflicting DLLs", MB_OK | MB_ICONEXCLAMATION);
	delete[] szMsg;
}

void HandleNonMutexedInstance(void) {
	// Find the address the non-mutexed code is at by finding where the
	// TE fix code jumps to.
	uint32_t dwAddress = NULL;
	switch (GetGameVersion()) {
	case 640:
		dwAddress = 0x65EC5E;
		break;

	case 641:
		dwAddress = 0x65EE3E;
		break;

	default:
		return;
	}

	dwAddress = *(uint32_t*)(dwAddress + 1);

	// Enumerate the DLLs loaded into the game to search for the module
	// belonging to that address.
	HMODULE hModules[512];
	HMODULE hBadModule = NULL;
	DWORD cbNeeded;

	if (EnumProcessModules(GetCurrentProcess(), hModules, sizeof(hModules), &cbNeeded)) {
		for (int i = 0; i < (int)(cbNeeded / sizeof(HMODULE)); i++) {
			MODULEINFO modInfo;
			GetModuleInformation(GetCurrentProcess(), hModules[i], &modInfo, sizeof(MODULEINFO));

			uint32_t dwBaseAddress = (uint32_t)hModules[i];
			uint32_t dwModuleSize = modInfo.SizeOfImage;

			if (dwAddress >= dwBaseAddress && dwAddress <= dwBaseAddress + dwModuleSize) {
				hBadModule = hModules[i];
				break;
			}
		}
	}

	// Produce an error message.
	HandleConflictingInstances(hBadModule);
}