/*
   Project: SC4Fix Patch Injector
   File: SC4FixInjector.cpp

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
#include <Windows.h>

void RaiseError(LPSTR szError)
{
	MessageBox(NULL, szError, "SC4Fix Shim", MB_OK | MB_ICONERROR);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// The shim relies on being placed in the same directory as both
	// "SimCity 4.exe" and "SC4Fix.dll"
	PROCESS_INFORMATION pi;
	STARTUPINFO si;

	ZeroMemory(&si, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);

	const LPSTR injectedDll = "SC4Fix.dll";
	const LPSTR injectionProcess = "SimCity 4.exe";

	int nModuleLen = strlen(injectedDll) + 1;
	int nTargetLen = strlen(injectionProcess) + 1;

	BOOL succeeded = CreateProcess(injectionProcess, GetCommandLine(), NULL, NULL, FALSE, CREATE_NEW_PROCESS_GROUP | CREATE_SUSPENDED, NULL, NULL, &si, &pi);
	if (!succeeded)
	{
		RaiseError("Failed to start process - are SimCity 4.exe, SC4Fix.dll and SC4Fix.shim.exe in the same path?");
		return 1;
	}

	void* lpAlloc = VirtualAllocEx(pi.hProcess, NULL, nModuleLen, MEM_COMMIT, PAGE_READWRITE);
	if (lpAlloc == NULL)
	{
		RaiseError("Could not allocate space for the DLL name in the process.");
		TerminateProcess(pi.hProcess, 0);
		return 2;
	}

	LPTHREAD_START_ROUTINE fnLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
	if (fnLoadLibrary == NULL)
	{
		RaiseError("Could not find LoadLibraryA position in kernel32.dll");
		TerminateProcess(pi.hProcess, 0);
		return 3;
	}

	SIZE_T bytesWritten;
	succeeded = WriteProcessMemory(pi.hProcess, lpAlloc, injectedDll, nModuleLen, &bytesWritten);

	if (!succeeded)
	{
		RaiseError("Failed to write DLL name to target process.");
		TerminateProcess(pi.hProcess, 0);
		return 4;
	}

	HANDLE hThread = CreateRemoteThread(pi.hProcess, NULL, 0, fnLoadLibrary, (void*)lpAlloc, 0, NULL);
	if (hThread == NULL)
	{
		RaiseError("Could not start LoadLibrary thread in SimCity 4.exe");
		TerminateProcess(pi.hProcess, 0);
		return 5;
	}

	DWORD dwReason = WaitForSingleObject(hThread, 20000);
	if (dwReason == WAIT_TIMEOUT)
	{
		RaiseError("The SC4Fix thread is hung.");
		TerminateProcess(pi.hProcess, 0);
		return 6;
	}
	else if (dwReason != WAIT_OBJECT_0)
	{
		RaiseError("Waiting for the injected SC4Fix DLL failed.");
		TerminateProcess(pi.hProcess, 0);
		return 7;
	}

	succeeded = GetExitCodeThread(pi.hThread, &dwReason);
	if (!succeeded)
	{
		RaiseError("Could not get thread exit code.");
		TerminateProcess(pi.hProcess, 0);
		return 8;
	}
	else if (dwReason == 0)
	{
		RaiseError("LoadLibrary failed in target process. Are SimCity 4.exe and SC4Fix.dll in the same path as the shim?");
		TerminateProcess(pi.hProcess, 0);
		return 9;
	}

	dwReason = ResumeThread(pi.hThread);
	if (dwReason == -1)
	{
		RaiseError("Could not resume main thread in SimCity 4.exe");
		TerminateProcess(pi.hProcess, 0);
		return 10;
	}

	return 0;
}