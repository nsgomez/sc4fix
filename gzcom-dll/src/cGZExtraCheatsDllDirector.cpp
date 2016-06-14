#include "../include/cIGZApp.h"
#include "../include/cIGZFrameWork.h"
#include "../include/cIGZMessage2.h"
#include "../include/cIGZMessageServer2.h"
#include "../include/cIGZMessageTarget2.h"
#include "../include/cISC4App.h"
#include "../include/cISC4RenderProperties.h"
#include "../include/cRZCOMDllDirector.h"
#include "../include/GZServPtrs.h"
#include <Windows.h>

static const uint32_t kExtraCheatsPluginCOMDirectorID = 0x8bbd9623;
static const uint32_t kGZIID_cISC4App = 0x26ce01c0;

class cSC4ExtraCheatsPluginCOMDirector : public cRZCOMDllDirector, public cIGZMessageTarget2
{
	public:
		/* Failing to explicitly delegate these methods results in some
		   ambiguity when resolving which virtual methods to use: those
		   from cIGZMessageTarget (which are pure abstract) or those from
		   cRZCOMDllDirector, and the compiler will complain. */
		bool QueryInterface(uint32_t riid, void** ppvObj) {
			return cRZCOMDllDirector::QueryInterface(riid, ppvObj);
		}

		uint32_t AddRef(void) {
			return cRZCOMDllDirector::AddRef();
		}

		uint32_t Release(void) {
			return cRZCOMDllDirector::Release();
		}

		uint32_t GetDirectorID() const {
			return kExtraCheatsPluginCOMDirectorID;
		}

		bool DoMessage(cIGZMessage2* pMessage) {
			if (pMessage->GetType() == 0xea8ae29a) {
				MessageBoxA(NULL, "City finished loading", NULL, NULL);
			}

			return true;
		}

		bool PreAppInit() {
			cIGZFrameWork* const pFramework = RZGetFrameWork();
			if (pFramework) {
				cIGZApp* const pApp = pFramework->Application();
				if (pApp) {
					cISC4App* pISC4App;
					if (pApp->QueryInterface(kGZIID_cISC4App, (void**)&pISC4App)) {
						pISC4App->SetDebugFunctionalityEnabled(true);
					}
				}
			}

			return true;
		}

		bool PostAppInit() {
			// The cRZSysServPtr will automatically try to receive the service
			// pointer for us.
			cIGZMessageServer2Ptr pMsgServ;
			if (pMsgServ) {
				pMsgServ->AddNotification(this, 0xea8ae29a);
			}

			return true;
		}

		bool OnStart(cIGZCOM* pCOM) {
			cIGZFrameWork* const pFramework = RZGetFrameWork();
			if (pFramework) {
				if (pFramework->GetState() < cIGZFrameWork::kStatePreAppInit) {
					pFramework->AddHook(this);
				}
				else {
					PreAppInit();
				}
			}
			return true;
		}
};