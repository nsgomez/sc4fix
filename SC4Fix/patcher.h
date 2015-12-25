#pragma once
#include <stdint.h>

#define ASMJMP(a) _asm { mov CPatcher::uJumpBuffer, a } _asm { jmp CPatcher::uJumpBuffer }

typedef void (*tfnHookFunc)(void);

class CPatcher {
public:

	static void InstallHook(uint32_t uAddress, void (*pfnFunc)(void));
	static void UninstallHook(uint32_t uAddress, uint8_t uFirstByte, uint32_t uOtherBytes);
	static void InstallCallHook(uint32_t uAddress, void (*pfnFunc)(void));
	static void InstallMethodHook(uint32_t uAddress, void (*pfnFunc)(void));

	static void UnprotectAll(void);

	static uint32_t uJumpBuffer;
};