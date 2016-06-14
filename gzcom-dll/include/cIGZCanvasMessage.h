#pragma once
#include "cIGZMessage2.h"

class cIGZCanvasMessage : public cIGZMessage2
{
	public:
		virtual cIGZCanvasMessage* Initialize(uint32_t dwCanvasEventID) = 0;
		virtual uint32_t EventType(void) = 0;
};