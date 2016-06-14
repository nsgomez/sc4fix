#pragma once
#include "cIGZUnknown.h"

class cISC424HourClock : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual int32_t SetVisualTimeMode(int32_t nTimeMode) = 0;
		virtual int32_t GetVisualTimeMode(void) = 0;

		virtual float GetTimePercentage(void) = 0;
		virtual int32_t SetTimePercentage(float& fPercentage) = 0;
		virtual float GetVisualTimePercentage(void) = 0;
		
		virtual uint32_t GetHour(void) = 0;
		virtual uint32_t SetHour(uint32_t dwHour) = 0;
		virtual uint32_t GetVisualHour(void) = 0;
		
		virtual uint32_t GetMinute(void) = 0;
		virtual uint32_t SetMinute(uint32_t dwMinute) = 0;
		virtual uint32_t GetVisualMinute(void) = 0;

		virtual uint32_t GetSeconds(void) = 0;
		virtual uint32_t SetSeconds(uint32_t dwSeconds) = 0;
		virtual uint32_t GetVisualSeconds(void) = 0;

		virtual uint32_t GetEventHour(bool bUnknown) = 0;
		
		virtual uint32_t GetTimeMagnification(float& fMagnificationOut) = 0;
		virtual uint32_t SetTimeMagnification(float fMagnification) = 0;
		
		virtual uint32_t GetTimeMagnificationMinMax(float& fMinOut, float& fMaxOut) = 0;
		virtual bool SetTimeMagnificationMinMax(float fMin, float fMax) = 0;

		virtual bool Pause(bool bUnknown) = 0;
		virtual bool IsPaused(void) = 0;

		virtual bool HiddenPause(bool bUnknown) = 0;
		virtual bool IsHiddenPaused(void) = 0;

		virtual bool IsNight(void) = 0;
		virtual void EnableDayNightTransitionNotifications(bool bToggle) = 0;
};