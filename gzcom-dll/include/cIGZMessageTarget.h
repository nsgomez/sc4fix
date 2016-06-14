#pragma once
#include "cIGZUnknown.h"

class cGZMessage;

class cIGZMessageTarget : public cIGZUnknown
{
	public:
		virtual bool DoMessage(cGZMessage& sMessage) = 0;
};