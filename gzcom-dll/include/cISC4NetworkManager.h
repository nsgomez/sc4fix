#pragma once
#include "cIGZUnknown.h"
#include "SC4Point.h"
#include <list>

class cISC4Lot;
class cISC4NetworkOccupant;
class cISC4NetworkTool;
class cISC4Occupant;
class cISC4OccupantFilter;
class cISC4OccupantManager;

class cISC4NetworkManager : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual cISC4NetworkTool* GetNetworkTool(int32_t nNetworkType, bool bCreateUnique) = 0;

		virtual bool DestroyNetworkOccupants(std::list<cISC4Occupant*> const& sOccupants) = 0;
		virtual void QueueRemovals(bool bShouldQueue) = 0;
		virtual bool RemoveOrReplaceOccupant(cISC4NetworkTool* pTool, cISC4Occupant* pOccupant, bool& bUnknownOut) = 0;

		virtual bool IsOccupantSubwayStation(cISC4Occupant* pOccupant) = 0;
		
		virtual bool FindPipeOccupant(intptr_t pPipeTool, int32_t nUnknown, intptr_t ppPipeOccupant) = 0; // nUnknown probably a cell
		virtual bool FindPipeConnectionOccupant(intptr_t pPipeTool, int32_t nUnknown, intptr_t ppPipeConnOccupant) = 0; // nUnknown probably a cell

		virtual bool GetAllIntersectionPieces(cISC4NetworkOccupant* pOccupant, std::list<cISC4Occupant*>& sList, cISC4OccupantManager* pManager, cISC4NetworkOccupant* pUnknown) = 0;
		virtual bool GetAllIntersectionPieces2(cISC4NetworkOccupant* pOccupant, std::list<cISC4Occupant*>& sList, cISC4OccupantManager* pManager, cISC4NetworkOccupant* pUnknown, cISC4OccupantFilter* pFilter) = 0;

		virtual uint32_t MapPreviewTexture(uint32_t dwUnknown1, uint8_t& cUnknown) = 0;
		virtual uint32_t MapShadowTexture(uint32_t dwUnknown1, uint8_t& cUnknown, uint32_t dwUnknown2, uint32_t dwUnknown3) = 0;
		virtual uint32_t MapPath(uint32_t dwUnknown1) = 0;

		virtual bool RegisterConstructionCrew(intptr_t pConstructionCrew) = 0;
		virtual bool UnregisterConstructionCrew(intptr_t pConstructionCrew) = 0;

		virtual cISC4OccupantFilter* GetWaterOccupantFilter(void) = 0;
		virtual cISC4OccupantFilter* GetSubwayOccupantFilter(void) = 0;
		
		virtual bool CreateConnectionNode(cISC4Occupant*& pOccupant, int32_t nNetworkType, SC4Point<int> const& sPoint, uint32_t dwUnknown1, uint32_t dwUnknown2, uint32_t dwUnknown3, uint8_t cUnknown) = 0;
		virtual bool AutoconnectLotNodes(cISC4Lot* pLot, std::list<cISC4Occupant*> const& sNodes) = 0;

		virtual char const* GetEnglishNetworkName(int32_t nNetworkType) = 0;

		virtual bool AddToRetrofitList(cISC4NetworkOccupant* pOccupant) = 0;
};