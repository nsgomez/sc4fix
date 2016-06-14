#pragma once
#include "cIGZUnknown.h"

class cISC4FeatureManager : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual bool IsFeatureEnabled(uint32_t dwFeatureID) = 0;
		virtual bool IsExpansionPackInstalled(uint32_t dwEPID) = 0;
		virtual uint32_t GetCurrentExpansionPack(void) = 0;
};