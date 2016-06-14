#pragma once
#include "cIGZUnknown.h"

class cIGZString;
class cISC4Region;

class cISC4Nation : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual void* GetRegionDirectory(void) = 0;
		virtual int GetRegionCount(void) = 0;
		
		virtual int GetActiveRegionIndex(void) = 0;
		virtual cISC4Region* GetActiveRegion(void) = 0;
		virtual cISC4Region* SetActiveRegion(cISC4Region* pRegion) = 0;

		virtual bool GetIndexOfCurrentRegionSettingInPreferences(int32_t& nIndexOut) = 0;
		
		virtual cISC4Region* GetRegion(uint32_t dwIndex) = 0;
		virtual intptr_t DeleteRegion(uint32_t dwIndex) = 0;
		virtual int32_t AddNewRegion(const cIGZString& szName) = 0;

		virtual bool ResetTutorialCities(void) = 0;

		virtual void* GetRegionDownloadDirectory(void) = 0;
		virtual float GetEconomyModifier(uint32_t dwDemandType) = 0;
};