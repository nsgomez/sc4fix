#pragma once
#include <cIGZUnknown.h>

class cIFXPatch : public cIGZUnknown
{
	public:
		virtual bool InstallPatch(bool bIsSteam) = 0;
		virtual bool UninstallPatch(void) = 0;
};