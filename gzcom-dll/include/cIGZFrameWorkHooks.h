#pragma once
#include "cIGZUnknown.h"

// This class is derived from Paul Pedriana's released code and should be perfect.
class cIGZFrameWorkHooks : public cIGZUnknown
{
	public:
		virtual bool PreFrameWorkInit(void) = 0;
		virtual bool PreAppInit(void) = 0;
		virtual bool PostAppInit(void) = 0;
		virtual bool PreAppShutdown(void) = 0;
		virtual bool PostAppShutdown(void) = 0;
		virtual bool PostSystemServiceShutdown(void) = 0;
		virtual bool AbortiveQuit(void) = 0;
		virtual bool OnInstall(void) = 0;
};