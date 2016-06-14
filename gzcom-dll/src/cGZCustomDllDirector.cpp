#include <stdio.h>
#include "../include/cIGZFrameWork.h"
#include "../include/cRZCOMDllDirector.h"

// This must be unique for every plugin. Generate a random 32-bit integer and use it.
// DO NOT REUSE DIRECTOR IDS EVER.
static const uint32_t kCustomCOMDirectorDirectorID = 0x06dcbef1;

// Objects provided by plugins must also have their own unique class IDs.
static const uint32_t kGZCLSID_cSomeObject = 0x46dcc1fc;

// This is a bare-bones example of a class that can be loaded into the game.
// Any DLLs you make should be derived off this example, as the other example
// (cGZExampleDllDirector) overrides basically every method just to demonstrate
// the functionality for no useful reason.
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
			return kCustomCOMDirectorDirectorID;
		}

		bool OnStart(cIGZCOM* pCOM) {
			// This automatically gets called by the framework after loading
			// the library.
			//
			// Register for callbacks so we can get PreFrameWorkInit,
			// PreAppInit, and other callbacks.
			RZGetFrameWork()->AddHook(static_cast<cIGZFrameWorkHooks*>(this));
			return true;
		}

		static cIGZUnknown* CreateSomeObject(void) {
			cIGZUnknown* pUnknown = nullptr;
			// Initialize an IGZUnknown implementation here.

			return pUnknown;
		}

		bool PreFrameWorkInit(void) { return true; }
		bool PreAppInit(void) { return true; }
		bool PostAppInit(void) { return true; }
		bool PreAppShutdown(void) { return true; }
		bool PostAppShutdown(void) { return true; }
		bool PostSystemServiceShutdown(void) { return true; }
		bool AbortiveQuit(void) { return true; }
		bool OnInstall(void) { return true; }
};