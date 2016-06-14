#pragma once
#include "cIGZUnknown.h"

class cIGZPersistDBSegment;
class cIGZString;
class cISC424HourClock;
class cISC4BudgetSimulator;
class cISC4DisasterLayer;
class cISC4HistoryWarehouse;
class cISC4LotManager;
class cISC4NetworkManager;
class cISC4PoliceSimulator;
class cISC4PollutionSimulator;
class cISC4ResidentialSimulator;
class cISC4Simulator;
class cISC4TutorialSystem;

class cISC4City : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual uint32_t GetCitySerialNumber(void) = 0;
		virtual cISC4City* SetCitySerialNumber(uint32_t dwSerial) = 0;
		virtual uint32_t GetNewOccupantSerialNumber(void) = 0;

		virtual bool GetOriginalLanguageAndCountry(uint32_t& dwLanguage, uint32_t& dwCountry) = 0;
		virtual bool GetLastLanguageAndCountry(uint32_t& dwLanguage, uint32_t& dwCountry) = 0;
		
		virtual bool GetCitySaveFilePath(cIGZString& szPath) = 0;
		virtual bool SetCitySaveFilePath(cIGZString const& szPath) = 0;

		virtual bool GetCityName(cIGZString& szPath) = 0;
		virtual bool SetCityName(cIGZString const& szPath) = 0;

		virtual bool GetCityNameChanged(void) = 0;
		virtual cISC4City* SetCityNameChanged(bool bToggle) = 0;

		virtual bool GetMayorName(cIGZString& szName) = 0;
		virtual bool SetMayorName(cIGZString const& szName) = 0;

		virtual bool GetCityDescription(cIGZString& szDescription) = 0;
		virtual bool SetCityDescription(cIGZString const& szDescription) = 0;

		virtual uint32_t GetBirthDate(void) = 0;
		virtual cISC4City* SetBirthDate(uint32_t dwDate) = 0;

		virtual bool GetEstablished(void) = 0;
		virtual bool SetEstablished(bool bEstablished) = 0;

		virtual int32_t GetDifficultyLevel(void) = 0;
		virtual cISC4City* SetDifficultyLevel(int32_t dwLevel) = 0;

		virtual intptr_t GetWorldPosition(float& fX, float& fZ) = 0;
		virtual cISC4City* SetWorldPosition(float fX, float fZ) = 0;

		virtual float GetWorldBaseElevation(void) = 0;
		virtual cISC4City* SetWorldBaseElevation(float fElevation) = 0;

		virtual int32_t GetWorldHemisphere(void) = 0;

		// intptr_t's are likely class instances
		virtual intptr_t GetDemolitionUtility(void) = 0;
		virtual cISC4HistoryWarehouse* GetHistoryWarehouse(void) = 0;
		virtual cISC4LotManager* GetLotManager(void) = 0;
		virtual intptr_t GetOccupantManager(void) = 0;
		virtual intptr_t GetPropManager(void) = 0;
		virtual intptr_t GetZoneManager(void) = 0;
		virtual intptr_t GetLotConfigurationManager(void) = 0;
		virtual cISC4NetworkManager* GetNetworkManager(void) = 0;
		virtual intptr_t GetDispatchManager(void) = 0;
		virtual intptr_t GetTrafficNetwork(void) = 0;
		virtual intptr_t GetPropDeveloper(void) = 0;
		virtual intptr_t GetNetworkLotManager(void) = 0;
		virtual intptr_t GetVehicleManager(void) = 0;
		virtual intptr_t GetPedestrianManager(void) = 0;
		virtual intptr_t GetAircraftManager(void) = 0;
		virtual intptr_t GetWatercraftManager(void) = 0;
		virtual intptr_t GetAutomataControllerManager(void) = 0;
		virtual intptr_t GetAutomataScriptSystem(void) = 0;
		virtual intptr_t GetCitySituationManager(void) = 0;

		virtual cISC4Simulator* GetSimulator(void) = 0;
		virtual intptr_t GetAuraSimulator(void) = 0;
		virtual cISC4BudgetSimulator* GetBudgetSimulator(void) = 0;
		virtual intptr_t GetBuildingDevelopmentSimulator(void) = 0;
		virtual intptr_t GetCommercialSimulator(void) = 0;
		virtual intptr_t GetCrimeSimulator(void) = 0;
		virtual intptr_t GetDemandSimulator(void) = 0;
		virtual intptr_t GetFireProtectionSimulator(void) = 0;
		virtual intptr_t GetFlammabilitySimulator(void) = 0;
		virtual intptr_t GetFloraSimulator(void) = 0;
		virtual intptr_t GetIndustrialSimulator(void) = 0;
		virtual intptr_t GetLandValueSimulator(void) = 0;
		virtual intptr_t GetNeighborsSimulator(void) = 0;
		virtual intptr_t GetOrdinanceSimulator(void) = 0;
		virtual intptr_t GetPlumbingSimulator(void) = 0;
		virtual cISC4PoliceSimulator* GetPoliceSimulator(void) = 0;
		virtual cISC4PollutionSimulator* GetPollutionSimulator(void) = 0;
		virtual intptr_t GetPowerSimulator(void) = 0;
		virtual cISC4ResidentialSimulator* GetResidentialSimulator(void) = 0;
		virtual intptr_t GetTrafficSimulator(void) = 0;
		virtual intptr_t GetWeatherSimulator(void) = 0;
		virtual intptr_t GetMySimAgentSimulator(void) = 0;
		
		virtual cISC4DisasterLayer* GetDisasterLayer(void) = 0;
		virtual intptr_t GetCivicBuildingSimulator(void) = 0;
		virtual intptr_t GetParkManager(void) = 0;
		virtual intptr_t GetZoneDeveloper(void) = 0;
		virtual intptr_t GetSeaportDeveloper(void) = 0;
		virtual intptr_t GetAirportDeveloper(void) = 0;
		virtual intptr_t GetLandfillDeveloper(void) = 0;
		virtual intptr_t GetLotDeveloper(void) = 0;
		virtual intptr_t GetTractDeveloper(void) = 0;

		virtual intptr_t GetAdvisorSystem(void) = 0;
		virtual cISC4TutorialSystem* GetTutorialSystem(void) = 0;

		virtual intptr_t GetSurfaceWater(void) = 0;
		virtual intptr_t GetTerrain(void) = 0;

		virtual intptr_t GetEffectsManager(void) = 0;
		
		virtual cISC424HourClock* Get24HourClock(void) = 0;
		
		virtual uint32_t GetCitySizeType(void) = 0;
		virtual bool SetSize(float fX, float fZ) = 0;
		virtual float SizeX(void) = 0;
		virtual float SizeZ(void) = 0;

		virtual float CellWidthX(void) = 0;
		virtual float CellWidthZ(void) = 0;

		virtual uint32_t CellCountX(void) = 0;
		virtual uint32_t CellCountZ(void) = 0;

		virtual int32_t PositionToCell(float fX, float fZ, int& cX, int& cZ) = 0;
		virtual int32_t CellCornerToPosition(int cX, int cZ, float& fX, float& fZ) = 0;
		virtual int32_t CellCenterToPosition(int cX, int cZ, float& fX, float& fZ) = 0;

		virtual bool LocationIsInBounds(float fX, float fZ) = 0;
		virtual bool CellIsInBounds(int cX, int cZ) = 0;
		virtual bool CellCornerIsInBounds(int cX, int cZ) = 0;

		virtual void ToggleSimulationMode(void) = 0;
		virtual bool IsInCityTimeSimulationMode(void) = 0;

		virtual int32_t EnableSave(void) = 0;
		virtual int32_t DisableSave(void) = 0;
		virtual bool IsSaveDisabled(void) = 0;

		virtual cISC4City* UIIncreaseLockCount(void) = 0;
		virtual int32_t UIDecreaseLockCount(void) = 0;
		virtual int32_t UIGetLockCount(void) = 0;

		virtual bool SaveObliterated(cIGZPersistDBSegment* pSegment) = 0;
};