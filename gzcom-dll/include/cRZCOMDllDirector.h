#pragma once
#include "cIGZCOMDirector.h"
#include "cIGZFrameWorkHooks.h"
#include "cRZBaseString.h"

// TODO: use EASTL instead, esp. since VS2015 is deprecating this
#include <hash_map>
#include <vector>

// This class is derived from Paul Pedriana's released code and should be perfect.
class cRZCOMDllDirector : public cIGZCOMDirector, public cIGZFrameWorkHooks
{
	public:
		cRZCOMDllDirector(void);
		virtual ~cRZCOMDllDirector(void);

	public:
		virtual uint32_t GetDirectorID(void) const = 0;

		virtual bool QueryInterface(uint32_t riid, void** ppvObj);
		virtual uint32_t AddRef(void);
		virtual uint32_t Release(void);

		virtual uint32_t RemoveRef(void);
		virtual uint32_t RefCount(void);

	public:
		typedef void (*DummyFunctionPtr)();
		typedef cIGZUnknown* (*FactoryFunctionPtr1)();
		typedef bool (*FactoryFunctionPtr2)(uint32_t, void**);

		bool InitializeCOM(cIGZCOM* pCOM, const cIGZString& sLibraryPath);
		bool OnStart(cIGZCOM* pCOM);
		bool GetLibraryPath(cIGZString& sLibraryPath);

		virtual bool GetClassObject(uint32_t rclsid, uint32_t riid, void** ppvObj);
		bool OnUnload(void) { return true; }
		cIGZFrameWork* FrameWork(void);
		cIGZCOM* GZCOM(void);
		void EnumClassObjects(ClassObjectEnumerationCallback pCallback, void* pContext);
		bool CanUnloadNow(void);
		void AddDirector(cRZCOMDllDirector* pCOMDirector);
		uint32_t GetHeapAllocatedSize(void);

	public:
		bool PreFrameWorkInit(void);
		bool PreAppInit(void);
		bool PostAppInit(void);
		bool PreAppShutdown(void);
		bool PostAppShutdown(void);
		bool PostSystemServiceShutdown(void);
		bool AbortiveQuit(void);
		bool OnInstall(void);

	protected:
		enum FactorFunctionType {
			kFactorFunctionType1 = 1,
			kFactorFunctionType2 = 2
		};

		enum GZIIDList {
			GZIID_cIGZFrameWorkHooks = 0x03FA40BF,
			kGZIID_cIGZCOMDirector = 0xA21EE941
		};

		void AddCls(uint32_t clsid, FactoryFunctionPtr1 pff1);
		void AddCls(uint32_t clsid, FactoryFunctionPtr2 pff2);

	protected:
		uint32_t mnRefCount;
		uint32_t mDirectorID;
		cRZBaseString msLibraryPath;
		cIGZCOM* mpCOM;
		cIGZFrameWork* mpFrameWork;

		typedef std::vector<cRZCOMDllDirector*> ChildDirectorArray;
		ChildDirectorArray mChildDirectorArray;

		typedef uint32_t ClassObjectID;
		typedef std::pair<DummyFunctionPtr, int32_t> FactoryFuncRecord;
		typedef std::hash_map<ClassObjectID, FactoryFuncRecord> ClassObjectMap;

		ClassObjectMap mClassObjectMap;
};

cRZCOMDllDirector* RZGetCOMDllDirector();
inline cIGZFrameWork* RZGetFrameWork() { return RZGetCOMDllDirector()->FrameWork(); }
inline cIGZFrameWork* RZGetFramework() { return RZGetCOMDllDirector()->FrameWork(); }