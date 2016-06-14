#pragma once
#include "cIGZUnknown.h"

class cIGZMessage2 : public cIGZUnknown
{
	public:
		virtual bool Create(uint32_t dwTypeIID, void** ppUnknown) = 0;

		virtual uint32_t GetType(void) = 0;
		virtual uint32_t SetType(uint32_t dwType) = 0;

		virtual bool operator==(cIGZMessage2 const& msgOther) = 0;
		virtual bool operator<(cIGZMessage2 const& msgOther) = 0;
};