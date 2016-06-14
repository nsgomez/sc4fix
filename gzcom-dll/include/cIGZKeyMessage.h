#pragma once
#include "cIGZMessage2.h"

class cIGZKeyMessage : public cIGZMessage2
{
	public:
		virtual uint32_t Initialize(uint32_t dwKeyEventID, uint32_t dwKey, uint32_t dwKeyFlags, uint32_t dwRepeatCount) = 0;

		virtual uint32_t EventType(void) = 0;
		virtual uint32_t Key(void) = 0;
		virtual uint32_t KeyFlags(void) = 0;
		virtual uint32_t RepeatCount(void) = 0;
};