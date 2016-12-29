#pragma once
#include "cIFXManager.h"
#include <cRZUnknown.h>

class cFXManager : public cIFXManager, public cRZUnknown
{
	public:
		uint32_t GetServiceID(void);
		cIGZSystemService* SetServiceID(uint32_t dwServiceId);

		int32_t GetServicePriority(void);
		bool IsServiceRunning(void);
		cIGZSystemService* SetServiceRunning(bool bRunning);

		bool Init(void);
		bool Shutdown(void);
		
		bool OnTick(void);
		bool OnIdle(void);

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
		bool m_bHasValidVersion;
		bool m_bRunningSteam;
};