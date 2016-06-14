#include <stdio.h>
#include <Windows.h>
#include "../include/cIGZFrameWork.h"
#include "../include/cRZCOMDllDirector.h"

static const uint32_t kCustomCOMDirectorDirectorID = 0x06dcbef1;
static const uint32_t kGZCLSID_cSomeObject = 0x46dcc1fc;

class cGZCustomDllDirector : public cRZCOMDllDirector
{
	public:
		cGZCustomDllDirector() {
			// Initialize variables here.
			// We can create objects using this COM director by satisfying
			// requests to GZCOM::GetClassObject if the class ID matches
			// our own.
			//AddCls(kGZCLSID_cSomeObject, CreateSomeObject);
		}

		virtual ~cGZCustomDllDirector() {
			// You could do something here, but everything except the OS is
			// dead by the time you get here.
		}

		uint32_t GetDirectorID() const {
			MessageBoxA(NULL, "GetDirectorID", NULL, MB_OK);
			return kCustomCOMDirectorDirectorID;
		}

		bool OnStart(cIGZCOM* pCOM) {
			// This automatically gets called by the framework after loading
			// the library.
			//
			// Register for callbacks so we can get PreFrameWorkInit,
			// PreAppInit, and other callbacks.
			MessageBoxA(NULL, "GZCustom: OnStart", NULL, MB_OK);
			RZGetFrameWork()->AddHook(static_cast<cIGZFrameWorkHooks*>(this));
			return true;
		}

		static cIGZUnknown* CreateSomeObject(void) {
			MessageBoxA(NULL, "GZCustom: CreateSomeObject", NULL, MB_OK);
			cIGZUnknown* pUnknown = nullptr;
			// Initialize an IGZUnknown implementation here.

			return pUnknown;
		}

		bool PreFrameWorkInit(void) { MessageBoxA(NULL, "GZCustom: PreFrameWorkInit", NULL, MB_OK); return true; }
		bool PreAppInit(void) { MessageBoxA(NULL, "GZCustom: PreAppInit", NULL, MB_OK); return true; }
		bool PostAppInit(void) { MessageBoxA(NULL, "GZCustom: PostAppInit", NULL, MB_OK); return true; }
		bool PreAppShutdown(void) { MessageBoxA(NULL, "GZCustom: PreAppShutdown", NULL, MB_OK); return true; }
		bool PostAppShutdown(void) { MessageBoxA(NULL, "GZCustom: PostAppShutdown", NULL, MB_OK); return true; }
		bool PostSystemServiceShutdown(void) { MessageBoxA(NULL, "GZCustom: PostSystemServiceShutdown", NULL, MB_OK); return true; }
		bool AbortiveQuit(void) { MessageBoxA(NULL, "GZCustom: AbortiveQuit", NULL, MB_OK); return true; }
		bool OnInstall(void) { MessageBoxA(NULL, "GZCustom: OnInstall", NULL, MB_OK); return true; }
};

cRZCOMDllDirector* RZGetCOMDllDirector() {
	static cGZCustomDllDirector sDirector;
	return &sDirector;
}