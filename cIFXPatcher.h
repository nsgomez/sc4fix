#pragma once
#include <cIGZUnknown.h>
#include <stdint.h>

typedef union {
	uint32_t dw;
	struct {
		uint8_t major;
		uint8_t minor;
		uint8_t patch;
		uint8_t build;
	} vtype;
} patchv;

class cIFXPatcher : public cIGZUnknown
{
	public:
		virtual bool InstallPatches(bool bUseSteamPatches) = 0;
		virtual bool UninstallPatches(void) = 0;

		virtual patchv GetPatcherVersion(void) = 0;
};