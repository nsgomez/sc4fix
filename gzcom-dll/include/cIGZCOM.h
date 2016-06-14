#pragma once
#include "cIGZUnknown.h"

class cGZCOMLibrary;
class cIGZCOMLibrary;
class cIGZFrameWork;
class cIGZString;
class cIGZSystemService;

// Vtable ordering used from the Mac version
class cIGZCOM : public cIGZUnknown
{
	public:
		virtual bool GetClassObject(uint32_t clsid, uint32_t iid, void** ppvObj) = 0;

		virtual cIGZFrameWork* FrameWork() = 0;

		virtual bool AddLibrary(const cIGZString& sPath) = 0;
		virtual void FreeUnusedLibraries() = 0;

		virtual bool CreateGuid(uint32_t* pGuid) = 0;
		virtual bool CreateGuids(uint32_t pGuidArray[], uint32_t nCount) = 0;

		virtual bool RealInit() = 0;
		virtual void RealShutdown() = 0;

		virtual cIGZSystemService* SetServiceRunning(bool bRunning) = 0;

		typedef bool(*GZCOMLibraryIterationFunction)(cGZCOMLibrary*, void*);
		virtual uint32_t EnumerateLibraries(cIGZCOMLibrary* pLibraries[], uint32_t& nCount) = 0;
		virtual void EnumerateLibraries(GZCOMLibraryIterationFunction iterationFunction, void* pContext) = 0;
};