#pragma once
#include "cIGZUnknown.h"
#include "SC4Rect.h"
#include <set>

class cISCPropertyHolder;
class cISC43DPlaceableObject;
class cS3DVector3;

class cISC4Occupant : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;
		virtual bool IsInitialized(void) = 0;
		
		virtual cISCPropertyHolder* AsPropertyHolder(void) = 0;
		
		virtual int32_t GetType(void) = 0;
		
		virtual bool GetPosition(cS3DVector3* pVector) = 0;
		virtual bool SetPosition(cS3DVector3 const* pVector) = 0;

		virtual cS3DVector3* GetBoundingBox(cS3DVector3* pTopLeftVec, cS3DVector3* pBottomRightVec) = 0;
		virtual bool GetBoundingCityCells(SC4Rect<long>& sRect) = 0;

		virtual uint32_t SetRemovalFlags(uint32_t dwFlags) = 0;
		virtual uint32_t UnsetRemovalFlags(uint32_t dwFlags) = 0;
		virtual bool CanRemove(uint32_t dwFlags) = 0;

		virtual bool PostOccupantMessage(uint32_t dwMessageID, uint32_t dwData) = 0;

		virtual uint32_t GetHighlight(void) = 0;
		virtual bool SetHighlight(uint32_t dwHighlight, bool bSendMessageNow) = 0;

		virtual uint8_t SetVisibility(bool bVisible, bool bSendMessage) = 0;

		virtual cISC43DPlaceableObject* GetPlaceableObject(void) = 0;
		virtual cISC43DPlaceableObject* GetOrCreatePlaceableObject(void) = 0;
		virtual cISC43DPlaceableObject* SetPlaceableObject(cISC43DPlaceableObject* pObject) = 0;

		virtual bool IsOccupantGroup(uint32_t dwGroup) = 0;
		virtual bool AddOccupantGroup(uint32_t dwGroup) = 0;
		virtual bool GetOccupantGroups(std::set<uint32_t>& sGroups) = 0;
		virtual bool GetOccupantManagerBBox(uint8_t* cBoxArray) = 0;
		virtual bool SetOccupantManagerBBox(uint8_t* cBoxArray) = 0; // array has 5 elements
		
		virtual bool GetLotTag(uint32_t& dwLotTag) = 0;
		virtual bool SetLotTag(uint32_t dwLotTag) = 0;

		virtual uint32_t SetFlag(uint32_t dwFlags) = 0;
		virtual cISC4Occupant* SetAllFlags(uint32_t dwFlags) = 0;
		virtual uint32_t ClearFlag(uint32_t dwFlags) = 0;
		virtual bool IsFlagSet(uint32_t dwFlags) = 0;
		virtual uint32_t GetFlags(void) = 0;
};