#pragma once
#include "cIGZUnknown.h"
#include <list>

class cISC4Occupant;
class cS3DVector3;
class SC4Percentage;

template <typename T> class cISC4SimGrid;

class cISC4PollutionSimulator : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual cISC4SimGrid<short>* GetPollutionGrid(uint32_t dwPollutionType) = 0;
		virtual uint16_t GetPollutionValue(uint32_t dwPollutionType, uint32_t dwCellX, uint32_t dwCellZ) = 0;
		virtual bool GetAirValue(uint32_t dwCellX, uint32_t dwCellZ, int16_t& wValue) = 0;
		virtual bool GetWaterValue(uint32_t dwCellX, uint32_t dwCellZ, int16_t& wValue) = 0;
		virtual bool GetGarbageValue(uint32_t dwCellX, uint32_t dwCellZ, int16_t& wValue) = 0;

		virtual int32_t GetAverageAirValue(void) = 0;
		virtual int32_t GetAverageWaterValue(void) = 0;
		virtual int32_t GetAverageGarbageValue(void) = 0;
		
		virtual bool IsAirPolluted(uint32_t dwCellX, uint32_t dwCellZ) = 0;
		virtual bool IsWaterPolluted(uint32_t dwCellX, uint32_t dwCellZ) = 0;
		virtual bool IsGarbageAccumulated(uint32_t dwCellX, uint32_t dwCellZ) = 0;
		virtual bool IsRadioactive(uint32_t dwCellX, uint32_t dwCellZ) = 0;

		virtual bool GetWorstAirTract(uint32_t& dwCellX, uint32_t& dwCellZ, int16_t& wValue) = 0;
		virtual bool GetWorstWaterTract(uint32_t& dwCellX, uint32_t& dwCellZ, int16_t& wValue) = 0;
		virtual bool GetWorstGarbageTract(uint32_t& dwCellX, uint32_t& dwCellZ, int16_t& wValue) = 0;

		virtual uint32_t GetGarbageSupply(void) = 0;
		virtual int32_t GetLandfillTileCapacity(void) = 0;
		virtual int32_t GetGarbageCapacity(void) = 0;

		virtual bool IsGarbageUncollected(void) = 0;
		virtual int32_t GetTotalGarbageUncollected(void) = 0;

		virtual uint32_t SetIsRadioactive(uint32_t dwCellX, uint32_t dwCellZ, bool bRadioactive) = 0;

		virtual bool SetAirValue(uint32_t dwCellX, uint32_t dwCellZ, int16_t wValue) = 0;
		virtual bool SetWaterValue(uint32_t dwCellX, uint32_t dwCellZ, int16_t wValue) = 0;
		virtual bool SetGarbageValue(uint32_t dwCellX, uint32_t dwCellZ, int16_t wValue) = 0;

		virtual bool AddToGarbageSupply(int32_t nGarbage) = 0;
		virtual bool SetGarbageCapacity(int32_t nCapacity) = 0;
		virtual int32_t GetMonthlyIncineratorCapacity(void) = 0;
		virtual int32_t GetMonthlyWasteToEnergyCapacity(void) = 0;
		virtual int32_t GetRecyclingCenterEffect(void) = 0;

		virtual int32_t GetGarbageAbductedPrevMonth(void) = 0;
		virtual int32_t GetGarbageProducedLastMonth(void) = 0;
		virtual int32_t GetGarbageImportedLastMonth(void) = 0;
		virtual int32_t GetGarbageExportedLastMonth(void) = 0;
		virtual int32_t GetGarbageRecycledLastMonth(void) = 0;
		virtual int32_t GetGarbageIncineratedLastMonth(void) = 0;
		virtual int32_t GetGarbageConvertedToEnergyLastMonth(void) = 0;
		virtual int32_t GetGarbageLandfilledLastMonth(void) = 0;

		virtual uint32_t GetIncineratorCount(void) = 0;
		virtual uint32_t GetWasteToEnergyBuildingCount(void) = 0;
		virtual uint32_t GetRecyclingCenterCount(void) = 0;
		virtual uint32_t GetWaterTreatmentPlantCount(void) = 0;
		
		virtual bool GetGarbageBuildings(std::list<cISC4Occupant*>& sList) = 0;
		virtual uint32_t GetBuildingGarbageCapacity(cISC4Occupant* pOccupant) = 0;
		virtual float GetGarbageScalingFactor(void) = 0;
		
		virtual bool IsActiveLandfill(uint32_t dwCellX, uint32_t dwCellZ) = 0;
		virtual bool SetIsActiveLandfill(uint32_t dwCellX, uint32_t dwCellZ, bool bActive) = 0;
		virtual int64_t GarbagePutInLandfill(int32_t nGarbage) = 0;
		
		virtual bool GetMaxCapacity(uint32_t dwProperty, cISC4Occupant* pOccupant, uint32_t& dwResult) = 0;
		virtual bool GetCurrentCapacity(uint32_t dwProperty, cISC4Occupant* pOccupant, uint32_t& dwResult) = 0;

		virtual bool GetRecyclingCenterMaxCapacity(cISC4Occupant* pOccupant, SC4Percentage& sCapacity) = 0;
		virtual bool GetRecyclingCenterCurrentCapacity(cISC4Occupant* pOccupant, SC4Percentage& sCapacity) = 0;

		virtual bool GetCurrentOccupantCondition(cISC4Occupant* pOccupant, SC4Percentage& sCapacity) = 0;
		virtual bool GetCurrentOccupantEfficiency(cISC4Occupant* pOccupant, SC4Percentage& sCapacity) = 0;
		
		virtual bool GetIncineratorUsedCapacity(cISC4Occupant* pOccupant, uint32_t& dwCapacity) = 0;
		virtual bool GetWasteToEnergyUsedCapacity(cISC4Occupant* pOccupant, uint32_t& dwCapacity) = 0;

		virtual bool GetIncineratorCurrentCapacity(cISC4Occupant* pOccupant, uint32_t& dwCapacity) = 0;
		virtual bool GetWasteToEnergyCurrentCapacity(cISC4Occupant* pOccupant, uint32_t& dwCapacity) = 0;

		virtual bool GetWaterTreatmentMaxCapacity(cISC4Occupant* pOccupant, uint32_t& dwCapacity) = 0;
		virtual bool GetWaterTreatmentCurrentCapacity(cISC4Occupant* pOccupant, uint32_t& dwCapacity) = 0;
		virtual bool GetWaterTreatmentUsedCapacity(cISC4Occupant* pOccupant, uint32_t& dwCapacity) = 0;

		virtual bool CalcOccupantMaintenanceCost(cISC4Occupant* pOccupant, uint64_t& dwCost) = 0;
		
		virtual void AddRadiationToCity(cS3DVector3& sCenter, float fRadiusX, float fRadiusZ) = 0;

		// Does this belong here? It's in the vtable...
		virtual int32_t GetMaxAirPollutionLevelForUI(void) = 0;
		virtual int32_t GetMaxWaterPollutionLevelForUI(void) = 0;
		virtual int32_t GetMaxGarbagePollutionLevelForUI(void) = 0;
		virtual int32_t GetMaxRadiationPollutionLevelForUI(void) = 0;
};