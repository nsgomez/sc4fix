#pragma once
#include "cIGZUnknown.h"

class cISC4DisasterInstanceFire;
class cISC4DisasterManager;
class cISC4Occupant;

class cISC4DisasterManagerFire : public cIGZUnknown
{
	public:
		virtual cISC4DisasterManager* AsISC4DisasterManager(void) = 0;

		virtual bool IgniteOccupant(cISC4Occupant* pOccupant) = 0;
		virtual bool IgniteCell(uint32_t dwCellX, uint32_t dwCellZ, bool bUseProbability, bool bTeleport, uint32_t dwFireIID) = 0;
		virtual bool ExtinguishCell(uint32_t dwCellX, uint32_t dwCellZ, uint32_t dwUnknown) = 0; // unknown may have to do with fire phase
		virtual bool QuickBurnCell(uint32_t dwCellX, uint32_t dwCellZ) = 0;
		virtual bool IgniteCellRadius(uint32_t dwCenterX, uint32_t dwCenterZ, float fRadiusX, float fRadiusZ) = 0;
		
		virtual int32_t SetCause(uint32_t dwCause) = 0;
		virtual int32_t GetCause(void) = 0;
		
		virtual cISC4DisasterInstanceFire* GetFireInstance(void) = 0;
};