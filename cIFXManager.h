#pragma once
#include <cIGZSystemService.h>
#include "cIFXPatcher.h"

class cIFXManager : public cIGZSystemService
{
	public:
		virtual bool LoadPatcher(cIFXPatcher* pPatcher) = 0;
		virtual bool UnloadCurrentPatcher(void) = 0;
		virtual bool IsPatcherLoaded(void) = 0;
		virtual patchv GetCurrentPatcherVersion(void) = 0;

		virtual bool IsSteamVersion(void) = 0;
};