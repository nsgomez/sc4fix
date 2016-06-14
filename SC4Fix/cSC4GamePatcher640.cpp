#include "cSC4GamePatcher640.h"

bool cSC4GamePatcher640::PatchTELotCrash(void) {
	memcpy(wTEPatchBytes_96D8E9, (void*)0x96D8E9, 5);
	memcpy(wTEPatchBytes_65EBA0, (void*)0x65EBA0, 5);

	CPatcher::InstallHook(0x96D8E9, Hook_Sub96D8E9);
	CPatcher::InstallHook(0x65EBA0, Hook_Sub65EBA0);

	return true;
}

bool cSC4GamePatcher640::PatchTitleBar(void) {
	memcpy(wTitlePatchBytes, (void*)0x44C2B0, 5);

	CPatcher::InstallHook(0x44C2B0, Hook_Sub44C2B0);

	return true;
}

bool cSC4GamePatcher640::UnpatchTELotCrash(void) {
	CPatcher::UninstallHook(0x96D8E9, wTEPatchBytes_96D8E9[0], *(uint32_t*)(&wTEPatchBytes_96D8E9[1]));
	CPatcher::UninstallHook(0x65EBA0, wTEPatchBytes_65EBA0[0], *(uint32_t*)(&wTEPatchBytes_65EBA0[1]));

	return true;
}

bool cSC4GamePatcher640::UnpatchTitleBar(void) {
	CPatcher::UninstallHook(0x44C2B0, wTitlePatchBytes[0], *(uint32_t*)(&wTitlePatchBytes[1]));

	return true;
}

void __declspec(naked) cSC4GamePatcher640::Hook_Sub96D8E9(void) {
	static void* pUnknown;

	_asm mov dword ptr ds:[esi+4ch], ecx
	_asm mov pUnknown, eax
	_asm pushad

	if (pUnknown == nullptr) {
		_asm popad
		RETJMP(0x96D93B);
	}

	_asm popad
	_asm inc dword ptr ds:[eax+4]
	RETJMP(0x96D93B);
}

void __declspec(naked) cSC4GamePatcher640::Hook_Sub65EBA0(void) {
	static void* pUnknown;

	_asm mov dword ptr ds:[eax], ebx
	_asm mov pUnknown,esi
	_asm pushad

	if (pUnknown == nullptr) {
		_asm popad
		RETJMP(0x65EC86);
	}

	_asm popad
	_asm mov ecx,dword ptr ds:[esi+18h]
	RETJMP(0x65EC63);
}

void __declspec(naked) cSC4GamePatcher640::Hook_Sub65EBA0_Pt2(void) {
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
	RETJMP(0x65EC8B);
}

void __declspec(naked) cSC4GamePatcher640::Hook_Sub44C2B0(void) {
	_asm mov edx, offset szCaption
	RETJMP(44C99Ch);
}