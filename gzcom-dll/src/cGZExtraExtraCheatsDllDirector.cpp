#include "../include/cIGZApp.h"
#include "../include/cIGZCheatCodeManager.h"
#include "../include/cIGZFrameWork.h"
#include "../include/cIGZMessage2.h"
#include "../include/cIGZMessageServer2.h"
#include "../include/cIGZMessage2Standard.h"
#include "../include/cIGZMessageTarget2.h"
#include "../include/cISC4App.h"
#include "../include/cISC4City.h"
#include "../include/cISC4PollutionSimulator.h"
#include "../include/cISC4SimGrid.h"
#include "../include/cRZAutoRefCount.h"
#include "../include/cRZBaseString.h"
#include "../include/cRZCOMDllDirector.h"
#include "../include/cS3DVector3.h"
#include "../include/GZCLSIDDefs.h"
#include "../include/GZServPtrs.h"
#include <Windows.h>

static const uint32_t kExtraExtraCheatsPluginCOMDirectorID = 0x5b76862b;
static const uint32_t kGZIID_cIGZCheatCodeManager = 0xa1085722;
static const uint32_t kGZIID_cISC4App = 0x26ce01c0;
static const uint32_t kGZMSG_CheatIssued = 0x230e27ac;

static const uint32_t kCheatSievertBeGone = 0x9e0c0b4d;
static const uint32_t kCheatChernobyl = 0x606a36f7;

static const char* kszCheatSievertBeGone = "SievertBeGone";
static const char* kszCheatChernobyl = "Chernobyl";

class cGZExtraExtraCheatsPluginCOMDirector : public cRZCOMDllDirector, public cIGZMessageTarget2
{
	public:
		/* Failing to explicitly delegate these methods results in some
		   ambiguity when resolving which virtual methods to use: those
		   from cIGZMessageTarget (which are pure abstract) or those from
		   cRZCOMDllDirector, and the compiler will complain. */
		bool QueryInterface(uint32_t riid, void** ppvObj) {
			if (riid == GZCLSID::kcIGZMessageTarget2) {
				*ppvObj = static_cast<cIGZMessageTarget2*>(this);
				AddRef();
				return true;
			}
			else {
				return cRZCOMDllDirector::QueryInterface(riid, ppvObj);
			}
		}

		uint32_t AddRef(void) {
			return cRZCOMDllDirector::AddRef();
		}

		uint32_t Release(void) {
			return cRZCOMDllDirector::Release();
		}

		uint32_t GetDirectorID() const {
			return kExtraExtraCheatsPluginCOMDirectorID;
		}

		bool DoMessage(cIGZMessage2* pMessage) {
			if (pMessage->GetType() == kGZMSG_CheatIssued) {
				cIGZMessage2Standard* pStandardMsg = static_cast<cIGZMessage2Standard*>(pMessage);

				uint32_t dwCheatID = pStandardMsg->GetData1();
				cIGZString* pszCheatData = static_cast<cIGZString*>(pStandardMsg->GetVoid2());

				ProcessCheat(dwCheatID, pszCheatData);
			}

			return true;
		}

		bool PreAppInit() {
			return true;
		}

		bool PostAppInit() {
			cIGZFrameWork* const pFramework = RZGetFrameWork();
			if (pFramework) {
				cIGZApp* const pApp = pFramework->Application();
				if (pApp) {
					cISC4App* pISC4App;
					if (pApp->QueryInterface(kGZIID_cISC4App, (void**)&pISC4App)) {
						cIGZCheatCodeManager* pCheatMgr = pISC4App->GetCheatCodeManager();
						if (pCheatMgr && pCheatMgr->QueryInterface(kGZIID_cIGZCheatCodeManager, (void**)&pCheatMgr)) {
							RegisterCheats(pCheatMgr);
						}
					}
				}
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

		bool AbortiveQuit() {
			return true;
		}

	protected:
		bool ProcessCheat(uint32_t dwCheatID, cIGZString const* szCheatText) {
			switch (dwCheatID) {
				case kCheatSievertBeGone: return SetAllRadiation(false);
				case kCheatChernobyl: return SetAllRadiation(true);
				default: return false;
			}
		}

		void RegisterCheats(cIGZCheatCodeManager* pCheatMgr) {
			// The message ID parameter has no effect, so just pass zero like
			// the rest of the game does.
			pCheatMgr->AddNotification2(this, 0);

			cRZBaseString szCheatName(kszCheatSievertBeGone);
			pCheatMgr->RegisterCheatCode(kCheatSievertBeGone, szCheatName);

			szCheatName.FromChar(kszCheatChernobyl);
			pCheatMgr->RegisterCheatCode(kCheatChernobyl, szCheatName);
		}

	protected:
		bool SetAllRadiation(bool bSetRadioactive) {
			cISC4AppPtr pApp;
			if (!pApp) {
				return false;
			}

			cRZAutoRefCount<cISC4City> pCity(pApp->GetCity());
			if (!pCity) {
				return false;
			}

			cRZAutoRefCount<cISC4PollutionSimulator> pPollution(pCity->GetPollutionSimulator());
			if (!pPollution) {
				return false;
			}

			cRZAutoRefCount<cISC4SimGrid<short>> pGrid(pPollution->GetPollutionGrid(3));
			if (!pGrid) {
				return false;
			}

			for (uint32_t i = 0; i < pCity->CellCountX(); i++) {
				for (uint32_t j = 0; j < pCity->CellCountZ(); j++) {
					pPollution->SetIsRadioactive(i, j, bSetRadioactive);
				}
			}

			//pPollution->SetIsRadioactive(31, 31, bSetRadioactive);
			
			return true;
		}
};

// You need to replace the director returned here for the game and this DLL
// to use the right director. This is the only place that it's necessary to
// do so.
cRZCOMDllDirector* RZGetCOMDllDirector() {
	static cGZExtraExtraCheatsPluginCOMDirector sDirector;
	return &sDirector;
}