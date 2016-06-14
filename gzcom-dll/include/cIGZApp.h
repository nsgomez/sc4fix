#pragma once
#include "cIGZUnknown.h"

class cIGZFrameWork;
class cIGZSystemService;

// Taken from the Mac vtable
class cIGZApp : public cIGZUnknown
{
	public:
		virtual cIGZSystemService* AsIGZSystemService(void) = 0;
		virtual char const* ModuleName(void) = 0; // This could be a cIGZString
		virtual cIGZFrameWork* FrameWork(void) = 0;

		virtual bool AddApplicationService(cIGZSystemService* pService) = 0;

		virtual bool PreFrameWorkInit(void) = 0;
		virtual bool PostFrameWorkInit(void) = 0;
		virtual bool PreFrameWorkShutdown(void) = 0;

		virtual bool GZRun(void) = 0;
		virtual bool LoadRegistry(void) = 0;

		virtual void AddDynamicLibrariesHere(void) = 0;
		virtual void AddCOMDirectorsHere(void) = 0;
		virtual void AddApplicationServicesHere(void) = 0;
};