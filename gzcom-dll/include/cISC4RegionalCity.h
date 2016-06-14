#pragma once
#include "cIGZUnknown.h"
#include <list>
#include <vector>

class cIGZString;
class cISC4City;
class cISC4NeighborConnection;
class cISC4NeighborDeal;
class SC4NewCityPreferences;

class cISC4RegionalCity : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual bool GetPosition(int32_t& nX, int32_t& nZ) = 0;
		virtual bool SetPosition(int32_t nX, int32_t nZ, bool bDoRearrange) = 0;

		virtual bool GetCitySize(int32_t& nX, int32_t& nZ) = 0;
		virtual bool SetCitySize(int32_t nX, int32_t nZ) = 0;

		virtual int32_t GetPopulation(void) = 0;
		virtual int32_t GetCommercialJobs(void) = 0;
		virtual int32_t GetIndustrialJobs(void) = 0;
		virtual float GetWorkforcePercentage(void) = 0;
		
		virtual int32_t GetMayorRating(void) = 0;
		virtual int32_t GetDifficultyLevel(void) = 0;
		virtual float GetTaxRate(uint32_t dwTaxType) = 0;
		
		virtual int32_t GetPopulation(uint32_t dwPopulationType) = 0;
		virtual int32_t GetExtrapolatedPopulation(uint32_t dwPopulationType) = 0;
		virtual int32_t GetAllowableExtrapolation(uint32_t dwPopulationType) = 0;
		virtual int32_t ExtrapolateGrowth(uint32_t dwPopulationType, float fAddedPop) = 0;

		virtual cISC4RegionalCity* FindConnection(int32_t nUnknown1, int32_t nUnknown2, int32_t nUnknown3) = 0;
		virtual bool GetAllConnections(std::list<cISC4NeighborConnection*>& sList) = 0;
		virtual bool ChangeSymmetricConnection(cISC4NeighborConnection* pConnection, bool bUnknown) = 0;

		virtual bool SetupPreferences(SC4NewCityPreferences* pPreferences) = 0;
		virtual bool UpdateCityCache(SC4NewCityPreferences* pPreferences) = 0;
		
		virtual bool SetupCity(cISC4City* pCity) = 0;
		virtual bool UpdateCityCache(cISC4City* pCity) = 0;

		virtual uint32_t GetCitySerialNumber(void) = 0;
		virtual bool SetCitySerialNumber(uint32_t dwSerialNumber) = 0;

		virtual bool GetOriginalLanguageAndCountry(int32_t& nLanguage, int32_t& nCountry) = 0;
		virtual bool GetLastLanguageAndCountry(int32_t& nLanguage, int32_t& nCountry) = 0;

		virtual bool GetCitySaveFilePath(cIGZString& sPath) = 0;
		virtual bool SetCitySaveFilePath(cIGZString const& sPath) = 0;

		virtual bool GetCityName(cIGZString& sName) = 0;
		virtual bool SetCityName(cIGZString const& sName) = 0;

		virtual bool GetMayorName(cIGZString& sName) = 0;
		virtual bool SetMayorName(cIGZString const& sName) = 0;

		virtual bool GetUtilityAdvisorName(cIGZString& sName) = 0;
		virtual bool SetUtilityAdvisorName(cIGZString const& sName) = 0;

		virtual bool GetCityDescription(cIGZString& sDescription) = 0;
		virtual bool SetCityDescription(cIGZString const& sDescription) = 0;
		
		virtual uint32_t GetBirthDate(void) = 0;
		virtual bool SetBirthDate(uint32_t dwBirthDate) = 0;

		virtual bool GetEstablished(void) = 0;
		virtual bool SetEstablished(bool bEstablished) = 0;

		virtual bool GetWorldPosition(float& fX, float& fZ) = 0;
		virtual bool SetWorldPosition(float fX, float fZ) = 0;

		virtual float GetWorldBaseElevation(void) = 0;
		virtual bool GetWorldBaseElevation(float fElevation) = 0;

		virtual int32_t GetWorldHemisphere(void) = 0;

		virtual float GetBudget(void) = 0;
		virtual bool SetBudget(float fBudget) = 0;

		virtual float GetIncome(void) = 0;
		virtual bool SetIncome(float fIncome) = 0;

		virtual float GetExported(int32_t nCommodity) = 0;
		virtual bool SetExported(int32_t nCommodity, float fExports) = 0;

		virtual float GetImported(int32_t nCommodity) = 0;
		virtual bool SetImported(int32_t nCommodity, float fImports) = 0;

		virtual float GetProduced(int32_t nCommodity) = 0;
		virtual bool SetProduced(int32_t nCommodity, float fProduced) = 0;

		virtual float GetDemanded(int32_t nCommodity) = 0;
		virtual bool SetDemanded(int32_t nCommodity, float fDemanded) = 0;

		virtual float GetCostPerUnit(int32_t nCommodity) = 0;
		virtual bool SetCostPerUnit(int32_t nCommodity, float fCostPerUnit) = 0;

		virtual float GetCommodityBalance(int32_t nCommodity) = 0;

		virtual uint32_t GetTutorialGUID(void) = 0;
		virtual bool SetTutorialGUID(uint32_t dwGUID) = 0;
		virtual bool IsTutorial(void) = 0;

		virtual bool UpdateLocalDeals(void) = 0;
		virtual bool SetLocalDeals(std::list<cISC4NeighborDeal*>& sList) = 0;
		virtual bool GetLocalDeals(std::list<cISC4NeighborDeal*>& sList) = 0;
		
		virtual bool UpdateImportExport(void) = 0;

		virtual bool GetPointsOfInterest(uint32_t dwPointOfInterestType, std::vector<uint32_t>& sList) = 0;
};