#pragma once
#include "cRZUnknown.h"
#include "patcher.h"

static const uint32_t kGZIID_cIRZGamePatcher = 0x70600611;

class cIRZGamePatcher : public cIGZUnknown
{
	public:
		virtual bool InstallPatches(void) = 0;
		virtual bool UninstallPatches(void) = 0;
};