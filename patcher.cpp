#include "patcher.h"
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

uint32_t CPatcher::uJumpBuffer;

void CPatcher::InstallHook(uint32_t uAddress, void (*pfnFunc)(void)) {
	*((uint8_t*)uAddress) = 0xE9;
	*((uint32_t*)(uAddress+1)) = ((uint32_t)pfnFunc) - uAddress - 5;
}

void CPatcher::UninstallHook(uint32_t uAddress, uint8_t uFirstByte, uint32_t uOtherBytes) {
	*((uint8_t*)uAddress) = uFirstByte;
	*((uint32_t*)(uAddress+1)) = uOtherBytes;
}

void CPatcher::InstallCallHook(uint32_t uAddress, void (*pfnFunc)(void)) {
	*((uint8_t*)uAddress) = 0xE8;
	*((uint32_t*)(uAddress+1)) = ((uint32_t)pfnFunc) - uAddress - 5;
}

void CPatcher::InstallMethodHook(uint32_t uAddress, void (*pfnFunc)(void)) {
	*((uint32_t*)uAddress) = (uint32_t)pfnFunc;
}

void CPatcher::UnprotectAll(void) {
	DWORD uOldProtect;
	VirtualProtect((void *)0x407000, 0x6FFFFF, PAGE_EXECUTE_READWRITE, &uOldProtect);
}