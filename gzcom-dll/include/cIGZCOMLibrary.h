#pragma once
#include "cIGZUnknown.h"

class cIGZCOMDirector;
class cIGZString;

// Vtable ordering from Mac version
class cIGZCOMLibrary : public cIGZUnknown
{
	public:
		virtual bool GetPath(cIGZString& szCopyTo) = 0;
		virtual cIGZCOMDirector* GetDirector(void) = 0;

		virtual uintptr_t GetHandle(void) = 0;
		virtual bool IsLoaded(void) const = 0;
};