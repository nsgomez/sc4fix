#include "cSC4GamePatcher641.h"
#include <string.h>

bool cSC4GamePatcher641::PatchTELotCrash(void) {
	memcpy(wTEPatchBytes_96D8E9, (void*)0x96DA1D, 5);
	memcpy(wTEPatchBytes_65EBA0, (void*)0x65EE3E, 5);
	
	CPatcher::InstallHook(0x96DA1D, Hook_Sub96D8E9);
	CPatcher::InstallHook(0x65EE3E, Hook_Sub65EBA0);

	return true;
}

bool cSC4GamePatcher641::PatchTitleBar(void) {
	memcpy(wTitlePatchBytes, (void*)0x44CA7A, 5);

	CPatcher::InstallHook(0x44CA7A, Hook_Steam_Sub44C2B0);

	return true;
}

bool cSC4GamePatcher641::UnpatchTELotCrash(void) {
	CPatcher::UninstallHook(0x96DA1D, wTEPatchBytes_96D8E9[0], *(uint32_t*)(&wTEPatchBytes_96D8E9[1]));
	CPatcher::UninstallHook(0x65EE3E, wTEPatchBytes_65EBA0[0], *(uint32_t*)(&wTEPatchBytes_65EBA0[1]));

	return true;
}

bool cSC4GamePatcher641::UnpatchTitleBar(void) {
	CPatcher::UninstallHook(0x44CA7A, wTitlePatchBytes[0], *(uint32_t*)(&wTitlePatchBytes[1]));

	return true;
}

void __declspec(naked) cSC4GamePatcher641::Hook_Sub96D8E9(void) {
	static void* pUnknown;

	_asm mov dword ptr ds:[esi+4ch], ecx
	_asm mov pUnknown, eax
	_asm pushad

	if (pUnknown == nullptr) {
		_asm popad
		RETJMP(0x96DA23);
	}

	_asm popad
	_asm inc dword ptr ds:[eax+4]
	RETJMP(0x96DA23);
}

void __declspec(naked) cSC4GamePatcher641::Hook_Sub65EBA0(void) {
	static void* pUnknown;

	_asm mov dword ptr ds:[eax], ebx
	_asm mov pUnknown,esi
	_asm pushad

	if (pUnknown == nullptr) {
		_asm popad
		RETJMP(0x65EE66);
	}

	_asm popad
	_asm mov ecx,dword ptr ds:[esi+18h]
	RETJMP(0x65EE43);
}

void __declspec(naked) cSC4GamePatcher641::Hook_Sub65EBA0_Pt2(void) {
	static void* pUnknown;

	_asm mov pUnknown, ecx
	_asm pushad

	if (pUnknown == nullptr) {
		_asm popad
		_asm xor edx,edx
	}
	else {
		_asm popad
		_asm mov edx,dword ptr ds:[ecx+4]
	}

	_asm fstp st
	RETJMP(0x65EE6B);
}

void __declspec(naked) cSC4GamePatcher641::Hook_Steam_Sub44C2B0(void) {
	_asm mov ecx, offset szCaption
	RETJMP(0x44CA80);
}