#pragma once
#include "cIGZUnknown.h"

class cISC4DisasterManager;

class cISC4DisasterInstance : public cIGZUnknown
{
	public:
		virtual bool Shutdown(void) = 0;

		virtual cISC4DisasterManager* GetManager(void) = 0;
		virtual uint32_t GetID(void) = 0;
		virtual bool GetLocation(int32_t& nX, int32_t& nY) = 0;
		virtual int32_t GetPhase(void) = 0;
};