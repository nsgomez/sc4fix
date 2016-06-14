#pragma once
#include "cIGZUnknown.h"
#include <list>
#include <vector>

class cISC4Occupant;
class SC4Percentage;

template <typename T> class cISC4SimGrid;

class cISC4ResidentialSimulator : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual intptr_t GetProximityMap(uint8_t cWealthType) = 0;
		
		virtual bool SchoolIsOnStrike(void) = 0;
		virtual bool HealthIsOnStrike(void) = 0;

		virtual bool EndSchoolStrike(void) = 0;
		virtual bool EndHealthStrike(void) = 0;

		virtual float ChanceOfSchoolStrike(void) = 0;
		virtual float ChanceOfHealthStrike(void) = 0;

		virtual float GetSchoolSystemRating(void) = 0;
		virtual float GetHealthSystemRating(void) = 0;

		virtual bool GetSchoolSystemTotals(std::list<int32_t> const& sData) = 0; // int32_t -> tQueryData
		virtual bool GetHospitalSystemTotals(std::list<int32_t> const& sData) = 0; // int32_t -> tQueryData

		virtual int32_t GetPopulation(void) = 0;
		virtual int32_t GetTotalCityEducationUpkeepCost(void) = 0; // probably a no-op
		virtual int32_t GetTotalCityHealthUpkeepCost(void) = 0; // probably a no-op

		virtual bool SetOccupantFundingPercentages(cISC4Occupant* pOccupant, SC4Percentage const& sSchoolFunding, SC4Percentage const& sHealthFunding, bool bUnknown) = 0;
		virtual bool GetOccupantFundingPercentages(cISC4Occupant* pOccupant, SC4Percentage& sSchoolFunding, SC4Percentage& sHealthFunding, bool bUnknown) = 0;

		virtual bool GetAverageEQGrid(cISC4SimGrid<float>*& pGrid, float* fMin, float* fMax) = 0;
		virtual bool GetAverageHQGrid(cISC4SimGrid<float>*& pGrid, float* fMin, float* fMax) = 0;

		virtual bool GetEQGrids(cISC4SimGrid<float>*& pGrid, cISC4SimGrid<float>* pUnknown1, cISC4SimGrid<float>* pUnknown2) = 0;
		virtual bool GetHQGrids(cISC4SimGrid<float>*& pGrid, cISC4SimGrid<float>* pUnknown1, cISC4SimGrid<float>* pUnknown2) = 0;
		virtual bool GetPopulationGrids(cISC4SimGrid<uint16_t>*& pGrid, cISC4SimGrid<uint16_t>* pUnknown1, cISC4SimGrid<uint16_t>* pUnknown2) = 0;

		virtual bool GetSchoolQueryData(cISC4Occupant* pOccupant, intptr_t pQueryData) = 0;
		virtual bool GetHospitalQueryData(cISC4Occupant* pOccupant, intptr_t pQueryData) = 0;

		virtual bool EstimateCurrentOccupantCapacity(cISC4Occupant* pOccupant, uint32_t& dwUnknown1, uint32_t& dwUnknown2) = 0;
		
		virtual int32_t GetCellLifeExpectancy(uint32_t dwCellX, uint32_t dwCellZ) = 0;
		virtual float GetCellWorkforcePercent (uint32_t dwCellX, uint32_t dwCellZ) = 0;
		
		virtual float GetGlobalWorkforcePercent(void) = 0;
		virtual float GetGlobalEQ(void) = 0;
		virtual float GetGlobalHQ(void) = 0;
		virtual float GetGlobalLE(void) = 0;

		virtual float GetCellEQ(uint32_t dwCellX, uint32_t dwCellZ) = 0;
		virtual float GetCellHQ(uint32_t dwCellX, uint32_t dwCellZ) = 0;
		
		virtual float GetCellEQByWealth(uint32_t dwCellX, uint32_t dwCellZ, uint8_t cWealthType) = 0;
		virtual float GetCellHQByWealth(uint32_t dwCellX, uint32_t dwCellZ, uint8_t cWealthType) = 0;

		virtual int32_t GetSchoolAverageGradeMap(void) = 0;
		virtual int32_t GetHospitalAverageGradeMap(void) = 0;
		virtual int32_t GetAverageAgeMap(void) = 0;

		virtual int32_t GetAverageNewAgeByWealth(uint8_t cWealthType) = 0;
		virtual bool GetEQMinAndMaxCellCoords(uint32_t& dwMinCellX, uint32_t& dwMinCellZ, uint32_t& dwMaxCellX, uint32_t& dwMaxCellZ, float& fMin, float& fMax) = 0;
		virtual bool GetHQMinAndMaxCellCoords(uint32_t& dwMinCellX, uint32_t& dwMinCellZ, uint32_t& dwMaxCellX, uint32_t& dwMaxCellZ, float& fMin, float& fMax) = 0;

		virtual bool GetOccupantCoverage(cISC4Occupant* pOccupant, SC4Percentage const& sEffectiveness, float& fRangeX, float& fRangeZ) = 0;

		virtual int32_t GetSchoolBuildingCount(void) = 0;
		virtual bool GetSchoolBuildings(std::list<cISC4Occupant*>& sBuildings, std::vector<uint32_t>& sUnknown) = 0;

		virtual int32_t GetHospitalBuildingCount(void) = 0;
		virtual bool GetHospitalBuildings(std::list<cISC4Occupant*>& sBuildings, std::vector<uint32_t>& sUnknown) = 0;

		virtual int32_t GetMaxEQ(void) = 0;
		virtual int32_t GetMaxHQ(void) = 0;

		virtual bool GetGlobalAutoBudgetForSchools(void) = 0;
		virtual bool SetGlobalAutoBudgetForSchools(bool bEnable) = 0;

		virtual bool GetGlobalAutoBudgetForHospitals(void) = 0;
		virtual bool SetGlobalAutoBudgetForHospitals(bool bEnable) = 0;

		virtual bool GetAutoBudget(void) = 0;
		virtual bool SetAutoBudget(bool bEnable) = 0;

		virtual bool EstimateIdealFunding(cISC4Occupant* pOccupant, SC4Percentage& sFunding) = 0;
		
		virtual void ToggleTractTracking(int32_t nUnknown1, int32_t nUnknown2) = 0;
};