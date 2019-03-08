/*
   Project: SC4Fix Patches for SimCity 4
   File: CensusNoDeveloperFix.cpp

   Copyright (c) 2019 Nelson Gomez (simmaster07)

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

#include "CensusNoDeveloperFix.h"

uint32_t CensusNoDeveloper::Sub6A5A00_InjectPoint;
uint32_t CensusNoDeveloper::Sub6A5A00_ContinueJump;

void __declspec(naked) CensusNoDeveloper::Hook_Sub6A5A00(void) {
	static void* pUnknown;

	_asm mov pUnknown, eax
	_asm pushad

	if (pUnknown == NULL) {
		_asm popad
		_asm xor eax, eax
		_asm pop edi
		_asm pop esi
		_asm pop ebp
		_asm pop ebx
		_asm add esp, 12
		_asm retn 8
	}
	else {
		_asm popad
		_asm mov edx, dword ptr ds:[eax]
		_asm mov ecx, eax
		_asm call dword ptr ds : [edx + 34h]
		RETJMP(Sub6A5A00_ContinueJump);
	}
}

void CensusNoDeveloper::InstallPatch(void) {
	// TODO: Everything seems to be offset by a certain
	// amount but there are probably keyframes for these
	// offsets that need to be taken into consideration.

	switch (GetGameVersion()) {
	case 640:
		Sub6A5A00_InjectPoint = 0x6A5B2A;
		Sub6A5A00_ContinueJump = 0x6A5B31;
		break;

	case 641:
		Sub6A5A00_InjectPoint = 0x6A5BFA;
		Sub6A5A00_ContinueJump = 0x6A5C01;
		break;

	default:
		break;
	}

	CPatcher::InstallHook(Sub6A5A00_InjectPoint, Hook_Sub6A5A00);
}