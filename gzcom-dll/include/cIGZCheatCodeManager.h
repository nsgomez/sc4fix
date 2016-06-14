#pragma once
#include "cIGZUnknown.h"

class cIGZMessageTarget;
class cIGZMessageTarget2;
class cIGZString;

class cIGZCheatCodeManager : public cIGZUnknown
{
	public:
		virtual bool RegisterCheatCode(uint32_t clsid, cIGZString const& szCheatName) = 0;
		virtual bool UnregisterCheatCode(uint32_t clsid) = 0;
		
		virtual bool AddNotification(cIGZMessageTarget* pTarget, uint32_t dwMessageID) = 0;
		virtual bool RemoveNotification(cIGZMessageTarget* pTarget, uint32_t dwMessageID) = 0;

		virtual bool AddNotification2(cIGZMessageTarget2* pTarget, uint32_t dwMessageID) = 0;
		virtual bool RemoveNotification2(cIGZMessageTarget2* pTarget, uint32_t dwMessageID) = 0;

		virtual cIGZCheatCodeManager* EnableCheatCodeHistory(bool bEnable) = 0;
		virtual bool ClearCheatCodeHistory(void* pUnknown, uint32_t& dwSizeOut) = 0;
		virtual bool SetCheatCodeSaveData(void const* pUnknown, uint32_t dwSize) = 0;

		virtual int32_t GetListOfAllCheatStrings(cIGZString** ppStringsOut, uint32_t& dwUnknown) = 0;
		
		virtual bool HasUserUsedCheat(uint32_t clsid) = 0;
		virtual bool GetCheatState(uint32_t clsid) = 0;
		virtual int32_t GetCheatsWithEnabledStates(uint32_t* pCLSIDsOut, uint32_t& dwCountOut) = 0;
		
		virtual bool SetCheatState(uint32_t clsid, bool bState) = 0;
		virtual bool SetStateShouldBeSaved(uint32_t clsid, bool bToggle) = 0;
		virtual bool ClearAllEnabledCheatStates(void) = 0;

		virtual bool SendCheatNotifications(cIGZString const& szCheatString, uint32_t dwCheatID) = 0;
		
		virtual bool DoesCheatCodeMatch(cIGZString const& szCheatName, uint32_t& dwUnknownOut) = 0;
		virtual bool DoDefaultCheatCodeProcessing(cIGZString const& szUnknown, uint32_t& dwUnknown) = 0;

		virtual bool EnableCheatCodes(bool bEnable, cIGZString const& szUnknown) = 0;
		virtual bool GetCheatCodesEnabled(void) = 0;

		virtual bool GetCheatCodePassword(uint8_t* pUnknown, uint32_t& dwPassword) = 0;
		virtual bool SetCheatCodePassword(uint8_t* pUnknown, uint32_t dwPassword) = 0;

		virtual bool SetEnableDisableStrings(cIGZString const& szUnknown1, cIGZString const& szUnknown2) = 0;
};