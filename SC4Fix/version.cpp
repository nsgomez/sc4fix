/*
   Project: SC4Fix Patches for SimCity 4
   File: version.cpp

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

#include "version.h"
uint16_t nGameVersion = 0;

uint64_t GetAssemblyVersion(HMODULE hModule) {
	TCHAR szVersionFile[MAX_PATH];
	GetModuleFileName(hModule, szVersionFile, MAX_PATH);

	// http://stackoverflow.com/a/940743
	DWORD  verHandle = NULL;
	UINT   size = 0;
	LPBYTE lpBuffer = NULL;
	DWORD  verSize = GetFileVersionInfoSize(szVersionFile, &verHandle);

	if (verSize > 0) {
		LPSTR verData = new char[verSize];
		if (GetFileVersionInfo(szVersionFile, verHandle, verSize, verData)
			&& VerQueryValue(verData, "\\", (VOID FAR* FAR*)&lpBuffer, &size)
			&& size > 0) {
			VS_FIXEDFILEINFO* verInfo = (VS_FIXEDFILEINFO*)lpBuffer;
			if (verInfo->dwSignature = 0xfeef04bd) {
				uint64_t qwValue = verInfo->dwFileVersionMS << 32;
				qwValue |= verInfo->dwFileVersionLS;

				return qwValue;
			}
		}

		delete[] verData;
	}

	return 0;
}

void DetermineGameVersion(void) {
	uint64_t qwFileVersion = GetAssemblyVersion(NULL);
	uint16_t wMajorVer = (qwFileVersion >> 48) & 0xFFFF;
	uint16_t wMinorVer = (qwFileVersion >> 32) & 0xFFFF;
	uint16_t wRevision = (qwFileVersion >> 16) & 0xFFFF;
	uint16_t wBuildNum = qwFileVersion & 0xFFFF;

	// 1.1.x.x
	if (qwFileVersion > 0 && wMajorVer == 1 && wMinorVer == 1) {
		nGameVersion = wRevision;
	}
	else {
		nGameVersion = 0;
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