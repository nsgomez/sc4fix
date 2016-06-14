#pragma once
#include "cIGZUnknown.h"

class cISC4DisasterInstance;
class cISC4DisasterManager;
class cISC4Occupant;

class cISC4DisasterLayer : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual bool EnableDisasters(bool bToggle) = 0;
		virtual bool DisastersEnabled(void) = 0;

		virtual cISC4DisasterManager* GetDisasterManager(uint32_t dwDisasterType) = 0;

		virtual bool DisasterHasBegun(cISC4DisasterInstance* pDisaster) = 0;
		virtual bool DisasterHasEnded(cISC4DisasterInstance* pDisaster) = 0;
		virtual bool IsADisasterOngoing(void) = 0;
		virtual bool GoToNextDisaster(void) = 0;

		virtual bool GetMostRecentDisasterLocation(cISC4DisasterInstance* pDisaster, int& nX, int& nY) = 0;
		virtual bool RegisterDisasterLocation(cISC4DisasterInstance* pDisaster, int nX, int nY, cISC4Occupant* pOccupant, int32_t nUnknown, bool bTeleportCam) = 0;
		virtual bool UnregisterDisasterLocations(cISC4DisasterInstance* pDisaster) = 0;
		virtual bool UnregisterDisasterLocationByOccupant(cISC4DisasterInstance* pDisaster, cISC4Occupant* pOccupant) = 0;
		virtual int32_t GetDisasterLocationCount(void) = 0;

		virtual bool GetDisasterLocationByIndex(int32_t nIndex, cISC4DisasterInstance** ppDisaster, int& nX, int& nY) = 0;
		virtual int32_t GetDisasterCost(void) = 0;
};