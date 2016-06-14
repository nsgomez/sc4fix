#pragma once
#include "cIGZUnknown.h"
#include <list>

class cIGZApp;
class cIGZCOM;
class cIGZFrameWorkHooks;
class cIGZSystemService;

// Reverse engineered the vtable order from the Mac version, hoping
// for the best.
class cIGZFrameWork : public cIGZUnknown
{
	public:
		enum FrameworkState
		{
			kStatePreFrameWorkInit = 1,
			kStatePreAppInit = 3,
			kStatePostAppInit = 6,
			kStatePreAppShutdown = 10,
			kStatePostAppShutdown = 11,
			kStatePostSystemServiceShutdown = 12
		};

		virtual bool AddSystemService(cIGZSystemService* pService) = 0;
		virtual bool RemoveSystemService(cIGZSystemService* pService) = 0;
		virtual bool GetSystemService(uint32_t srvid, uint32_t riid, void** ppService) = 0;
		virtual bool EnumSystemServices(void* enumerator, cIGZUnknown* pUnknown, uint32_t dwUnknown) = 0; // ??? - enumerator is a function but what is prototype?

		virtual bool AddHook(cIGZFrameWorkHooks* pHooks) = 0;
		virtual bool RemoveHook(cIGZFrameWorkHooks* pHooks) = 0;

		virtual bool AddToTick(cIGZSystemService* pService) = 0;
		virtual bool RemoveFromTick(cIGZSystemService* pService) = 0;

		virtual bool AddToOnIdle(cIGZSystemService* pService) = 0;
		virtual bool RemoveFromOnIdle(cIGZSystemService* pService) = 0;
		
		virtual int32_t GetOnIdleInterval(void) = 0;
		virtual bool SetOnIdleInterval(int32_t nInterval) = 0;

		virtual int32_t OnTick(uint32_t dwUnknown) = 0;
		virtual cIGZFrameWork* OnIdle(void) = 0;

		virtual bool IsTickEnabled(void) = 0;
		virtual cIGZFrameWork* ToggleTick(bool bTick) = 0;

		virtual int32_t Quit(int32_t nUnknown) = 0;
		virtual void AbortiveQuit(int32_t nUnknown) = 0;
		
		virtual char* CommandLine(void) = 0;
		virtual bool IsInstall(void) = 0;

		virtual cIGZCOM* GetCOMObject(void) = 0;
		virtual int32_t GetState(void) = 0;

		virtual void* GetDebugStream(void) = 0; // unknown ret type
		virtual int32_t DefaultDebugStream(void) = 0; // int??
		virtual int32_t DebugStream(void) = 0; // int??
		virtual bool SetDebugStream(void* pIGZDebugStream) = 0; // is actually cIGZDebugStream
		virtual bool SetDebugLevel(int32_t nLevel) = 0;
		virtual int32_t GetDebugLevel(void) = 0;

		virtual int32_t StdOut(void) = 0; // ???
		virtual int32_t StdErr(void) = 0; // ???
		virtual int32_t StdIn(void) = 0; // ???

		virtual void* GetStream(void) = 0; // unknown ret type
		virtual bool SetStream(int32_t nUnknown, cIGZUnknown* pUnknown) = 0; // ???

		virtual bool SetApplication(cIGZApp* const pIGZApp) = 0;
		virtual cIGZApp* const Application(void) = 0;

		virtual void ReportException(char const* szExcText) = 0;
		virtual void* ExceptionNotificationObj(void) = 0; // actual return type unknown
};