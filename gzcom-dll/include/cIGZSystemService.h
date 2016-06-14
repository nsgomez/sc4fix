#pragma once
#include "cIGZUnknown.h"

// Reverse engineered from the Mac vtable
class cIGZSystemService : public cIGZUnknown
{
	public:
		virtual uint32_t GetServiceID(void) = 0;
		virtual cIGZSystemService* SetServiceID(uint32_t dwServiceId) = 0;

		virtual int32_t GetServicePriority(void) = 0;
		virtual bool IsServiceRunning(void) = 0;
		virtual cIGZSystemService* SetServiceRunning(bool bRunning) = 0;

		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;
		
		virtual bool OnTick(void) = 0;
		virtual bool OnIdle(void) = 0;
};