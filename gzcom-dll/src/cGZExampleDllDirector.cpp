#include <stdio.h>
#include <Windows.h>
#include "../include/cIGZFrameWork.h"
#include "../include/cRZCOMDllDirector.h"

#define DEMOMSG(x) MessageBoxA(NULL, x, "cGZExampleDllDirector", MB_OK)

// This must be unique for every plugin. Generate a random 32-bit integer and use it.
// DO NOT REUSE DIRECTOR IDS EVER.
static const uint32_t kCustomCOMDirectorDirectorID = 0x98c1304f;

// This is an example director class that pops up message boxes on every event
// to show you that it works.
class cGZExampleDllDirector : public cRZCOMDllDirector
{
	public:
		cGZExampleDllDirector() {
			// Initialize variables here.
			// We can create objects using this COM director by satisfying
			// requests to GZCOM::GetClassObject if the class ID matches
			// our own.
			DEMOMSG("constructor");
		}

		virtual ~cGZExampleDllDirector() {
			// You could do something here, but everything except the OS is
			// dead by the time you get here.
			DEMOMSG("destructor");
		}

		uint32_t GetDirectorID() const {
			DEMOMSG("GetDirectorID");
			return kCustomCOMDirectorDirectorID;
		}

		bool QueryInterface(uint32_t riid, void** ppvObj) {
			DEMOMSG("QueryInterface");
			return cRZCOMDllDirector::QueryInterface(riid, ppvObj);
		}

		uint32_t AddRef(void) {
			DEMOMSG("AddRef");
			return cRZCOMDllDirector::AddRef();
		}

		uint32_t Release(void) {
			DEMOMSG("Release");
			return cRZCOMDllDirector::Release();
		}

		uint32_t RemoveRef(void) {
			//DEMOMSG("RemoveRef");
			return cRZCOMDllDirector::RemoveRef();
		}

		uint32_t RefCount(void) {
			DEMOMSG("RefCount");
			return cRZCOMDllDirector::RefCount();
		}

		bool InitializeCOM(cIGZCOM* pCOM, const cIGZString& sLibraryPath) {
			DEMOMSG("InitializeCOM");
			return cRZCOMDllDirector::InitializeCOM(pCOM, sLibraryPath);
		}

		bool OnStart(cIGZCOM* pCOM) {
			DEMOMSG("OnStart");
			RZGetFrameWork()->AddHook(static_cast<cIGZFrameWorkHooks*>(this));
			return cRZCOMDllDirector::OnStart(pCOM);
		}

		bool GetLibraryPath(cIGZString& sLibraryPath) {
			DEMOMSG("GetLibraryPath");
			return cRZCOMDllDirector::GetLibraryPath(sLibraryPath);
		}

		bool GetClassObject(uint32_t rclsid, uint32_t riid, void** ppvObj) {
			DEMOMSG("GetClassObject");
			return cRZCOMDllDirector::GetClassObject(rclsid, riid, ppvObj);
		}

		bool OnUnload(void) {
			DEMOMSG("OnUnload");
			return cRZCOMDllDirector::OnUnload();
		}

		cIGZFrameWork* FrameWork(void) {
			DEMOMSG("FrameWork");
			return cRZCOMDllDirector::FrameWork();
		}

		cIGZCOM* GZCOM(void) {
			DEMOMSG("GZCOM");
			return cRZCOMDllDirector::GZCOM();
		}

		void EnumClassObjects(ClassObjectEnumerationCallback pCallback, void* pContext) {
			DEMOMSG("EnumClassObjects");
			cRZCOMDllDirector::EnumClassObjects(pCallback, pContext);
		}

		bool CanUnloadNow(void) {
			DEMOMSG("CanUnloadNow");
			return cRZCOMDllDirector::CanUnloadNow();
		}

		void AddDirector(cRZCOMDllDirector* pCOMDirector) {
			DEMOMSG("AddDirector");
			cRZCOMDllDirector::AddDirector(pCOMDirector);
		}

		uint32_t GetHeapAllocatedSize(void) {
			DEMOMSG("GetHeapAllocatedSize");
			return cRZCOMDllDirector::GetHeapAllocatedSize();
		}

		bool PreFrameWorkInit(void) {
			DEMOMSG("PreFrameWorkInit");
			return true;
		}

		bool PreAppInit(void) {
			DEMOMSG("PreAppInit");
			return true;
		}

		bool PostAppInit(void) {
			DEMOMSG("PostAppInit");
			return true;
		}

		bool PreAppShutdown(void) {
			DEMOMSG("PreAppShutdown");
			return true;
		}

		bool PostAppShutdown(void) {
			DEMOMSG("PostAppShutdown");
			return true;
		}

		bool PostSystemServiceShutdown(void) {
			DEMOMSG("PostSystemServiceShutdown");
			return true;
		}

		bool AbortiveQuit(void) {
			DEMOMSG("AbortiveQuit");
			return true;
		}

		bool OnInstall(void) {
			DEMOMSG("OnInstall");
			return true;
		}
};