#pragma once
#include "cIGZMessage2.h"

class cRZPoint;

class cIGZMouseMessage : public cIGZMessage2
{
	public:
		virtual uint32_t Initialize(uint32_t dwMouseEventID, cRZPoint const& sPosition, uint32_t dwKeyFlags, int32_t lWheelDelta) = 0;

		virtual uint32_t EventType(void) = 0;
		virtual cRZPoint const& Position(void) = 0;
		virtual int32_t WheelDelta(void) = 0;
		virtual uint32_t KeyFlags(void) = 0;
};