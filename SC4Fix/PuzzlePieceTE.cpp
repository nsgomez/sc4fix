/*
   Project: SC4Fix Patches for SimCity 4
   File: PuzzlePieceTE.cpp

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

#include "PuzzlePieceTE.h"

uint32_t PuzzlePieceTE::Sub96D8E9_InjectPoint;
uint32_t PuzzlePieceTE::Sub96D8E9_ContinueJump;

uint32_t PuzzlePieceTE::Sub65EBA0_InjectPoint;
uint32_t PuzzlePieceTE::Sub65EBA0_NullJump;
uint32_t PuzzlePieceTE::Sub65EBA0_ContinueJump;

uint32_t PuzzlePieceTE::Sub65EBA0_Pt2_ContinueJump;

//----------------------------------------------------------
//--- FIX CRASH WHEN HOVERING PUZZLE PIECES OVER LE LOTS ---
// Seems to be a null dereference issue though I don't have
// many details as to what exactly causes it.
//----------------------------------------------------------
void __declspec(naked) PuzzlePieceTE::Hook_Sub96D8E9(void) {
	static void* pUnknown;

	_asm mov dword ptr ds:[esi+4ch], ecx
	_asm mov pUnknown, eax
	_asm pushad

	if (pUnknown == NULL) {
		_asm popad
		RETJMP(Sub96D8E9_ContinueJump);
	}

	_asm popad
	_asm inc dword ptr ds:[eax+4]
	RETJMP(Sub96D8E9_ContinueJump);
}

void __declspec(naked) PuzzlePieceTE::Hook_Sub65EBA0(void) {
	static void* pUnknown;

	_asm mov dword ptr ds:[eax], ebx
	_asm mov pUnknown,esi
	_asm pushad

	if (pUnknown == NULL) {
		_asm popad
		RETJMP(Sub65EBA0_NullJump);
	}

	_asm popad
	_asm mov ecx,dword ptr ds:[esi+18h]
	RETJMP(Sub65EBA0_ContinueJump);
}

// This is especially weird: whatever was at ecx is
// tested to see if it's null, and if it is, it jumps
// to some cleanup code which dereferences it anyway.
void __declspec(naked) PuzzlePieceTE::Hook_Sub65EBA0_Pt2(void) {
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
	RETJMP(Sub65EBA0_Pt2_ContinueJump);
}

void PuzzlePieceTE::InstallPatch(void) {
	// TODO: Everything seems to be offset by a certain
	// amount but there are probably keyframes for these
	// offsets that need to be taken into consideration.

	switch (GetGameVersion()) {
	case 640:
		Sub96D8E9_InjectPoint = 0x96D935;
		Sub96D8E9_ContinueJump = 0x96D93B;

		Sub65EBA0_InjectPoint = 0x65EC5E;
		Sub65EBA0_NullJump = 0x65EC86;
		Sub65EBA0_ContinueJump = 0x65EC63;

		Sub65EBA0_Pt2_ContinueJump = 0x65EC8B;
		break;

	case 641:
		Sub96D8E9_InjectPoint = 0x96DA1D;
		Sub96D8E9_ContinueJump = 0x96DA23;

		Sub65EBA0_InjectPoint = 0x65EE3E;
		Sub65EBA0_NullJump = 0x65EE66;
		Sub65EBA0_ContinueJump = 0x65EE43;

		Sub65EBA0_Pt2_ContinueJump = 0x65EE6B;
		break;

	default:
		break;
	}

	CPatcher::InstallHook(Sub65EBA0_InjectPoint, Hook_Sub96D8E9);
	CPatcher::InstallHook(Sub65EBA0_InjectPoint, Hook_Sub65EBA0);
	CPatcher::InstallHook(Sub65EBA0_NullJump, Hook_Sub65EBA0_Pt2);
}