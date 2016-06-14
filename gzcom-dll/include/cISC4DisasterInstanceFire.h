#pragma once
#include "cIGZUnknown.h"
#include "SC4Rect.h"

class cISC4Occupant;

class cISC4DisasterInstanceFire : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Update(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual bool Ignite(cISC4Occupant* pOccupant, bool bIgnorePause, uint32_t dwFireIID, bool bTeleport) = 0;
		virtual bool IgniteCell(uint32_t dwCellX, uint32_t dwCellZ, bool bUseProbability, bool bTeleport, uint32_t dwFireIID) = 0;
		virtual bool ExtinguishCell(uint32_t dwCellX, uint32_t dwCellZ, uint32_t dwUnknown) = 0; // unknown may have to do with fire phase
		virtual bool QuickBurnCell(uint32_t dwCellX, uint32_t dwCellZ) = 0;
		virtual bool IgniteCellRadius(uint32_t dwCenterX, uint32_t dwCenterZ, float fRadiusX, float fRadiusZ) = 0;
		virtual bool Extinguish(cISC4Occupant* pOccupant) = 0;
		virtual bool BurnDown(cISC4Occupant* pOccupant) = 0;
		
		virtual int32_t SetCause(uint32_t dwCause) = 0;
		virtual int32_t GetCause(void) = 0;

		virtual int32_t GetFireCountInCellRect(SC4Rect<long>& sRect) = 0;
		virtual int32_t GetFireCount(void) = 0;
};