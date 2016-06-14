#pragma once
#include <cIGZUnknown.h>

class cISC4Patcher : public cIGZUnknown
{
	public:
		virtual uint32_t GetVersion(void) = 0;
		virtual bool TriggerUpdateWarning(void) = 0;
		
		virtual bool UnregisterPatcher(void) = 0;
};