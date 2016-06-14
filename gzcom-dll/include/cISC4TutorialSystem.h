#pragma once
#include "cIGZUnknown.h"

class cISCLua;
class cISC4TutorialTask;
class cISC4WinCatalogView;

class cISC4TutorialSystem : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual bool startTutorial(void) = 0;
		virtual bool endTutorial(bool bEndTutorialRegistry) = 0;

		virtual cISCLua* GetScriptingContext(void) = 0;

		virtual bool IsTutorial(void) = 0;
		virtual bool IsEdgeScrollingAllowed(void) = 0;

		virtual cISC4TutorialTask* GetCurrentTask(void) = 0;
		virtual int32_t GetTutorialTaskNumber(void) = 0;
		virtual int32_t GetTutorialGUID(void) = 0;

		virtual bool FilterMessage(uint32_t dwMessageID) = 0;
		
		virtual cISC4TutorialSystem* ShowUIHintsForUsers(void) = 0;

		virtual bool HandleCatalogMenu(cISC4WinCatalogView* pMenu) = 0;
		virtual bool FilterLeftMouseClick(int32_t& nX, int32_t& nY, int32_t nUnknown) = 0;

		virtual bool ResetTutorialNumAndIndex(int32_t nUnknown1, int32_t nUnknown2) = 0;
};