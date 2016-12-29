#pragma once
#include <cIGZUnknown.h>
#include <cIGZString.h>

class cIFXPatch : public cIGZUnknown
{
	public:
		virtual bool InstallPatch(bool bIsSteam) = 0;
		virtual bool UninstallPatch(void) = 0;

		virtual const cIGZString& GetName(void) const = 0;
		virtual const cIGZString& GetAuthor(void) const = 0;
		virtual const cIGZString& GetDescription(void) const = 0;
};