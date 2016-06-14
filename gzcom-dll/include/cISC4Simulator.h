#pragma once
#include "cIGZUnknown.h"
#include <vector>

class cIGZDate; // todo
class cIGZMessageTarget2;
class cIGZString;

class cISC4Simulator : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual bool GetSimStartDate(cIGZDate& sDate) = 0;
		
		virtual cIGZDate* GetSimDate(void) = 0;
		virtual int32_t GetSimDateNumber(void) = 0;

		virtual bool Pause(void) = 0;
		virtual bool HiddenPause(void) = 0;
		virtual bool EmergencyPause(void) = 0;
		
		virtual bool Resume(void) = 0;
		virtual bool HiddenResume(void) = 0;
		virtual bool EmergencyResume(void) = 0;

		virtual bool IsPaused(void) = 0;
		virtual bool IsHiddenPaused(void) = 0;
		virtual bool IsEmergencyPaused(void) = 0;
		virtual bool IsAnyPaused(void) = 0;

		// NOTE: dwAgentType <= 10
		virtual bool AddAgent(cIGZMessageTarget2* pAgent, uint32_t dwAgentType, cIGZString const& szAgentName, uint32_t dwUnknownFlags) = 0;
		virtual bool RemoveAgent(cIGZMessageTarget2* pAgent, uint32_t dwAgentType) = 0;
		virtual bool RemoveAgent(cIGZMessageTarget2* pAgent) = 0;
		virtual bool RemoveAllAgents(void) = 0;
		virtual bool RemoveAllAgents(uint32_t dwAgentType) = 0;
		virtual bool EnumerateAgentsByName(std::vector<cIGZString>& sAgents) = 0;
		virtual bool GetAgentEnabled(cIGZString const& szAgentName) = 0;
		virtual bool SetAgentEnabled(cIGZString const& szAgentName, bool bEnabled) = 0;

		virtual int32_t GetSimSpeed(void) = 0;
		virtual bool SetSimSpeed(int32_t lSpeed) = 0;

		virtual int32_t GetSimTime(void) = 0;
		virtual bool SetSimTime(int32_t lTime) = 0;

		virtual bool SetMaxMillisecondsPerTick(uint32_t dwTime) = 0;
		
		virtual float GetAnimationTimeDilation(void) = 0;

		virtual bool SetCityEstablished(bool bEstablished) = 0;
};