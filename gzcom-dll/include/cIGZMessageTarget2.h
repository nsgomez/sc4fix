#pragma once
#include "cIGZUnknown.h"

class cIGZMessage2;

class cIGZMessageTarget2 : public cIGZUnknown
{
	public:
		virtual bool DoMessage(cIGZMessage2* pMessage) = 0;
};