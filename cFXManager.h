#pragma once
#include "cIFXManager.h"
#include <cRZUnknown.h>

class cFXManager : public cIFXManager, public cRZUnknown
{
	public:
		cFXManager(void);
		virtual ~cFXManager(void);

		bool LoadPatcher(cIFXPatcher* pPatcher);
		bool UnloadCurrentPatcher(void);
		bool IsPatcherLoaded(void);
		patchv GetCurrentPatcherVersion(void);

		bool IsSteamVersion(void);

	private:
		cIFXPatcher* m_pCurPatcher;
};