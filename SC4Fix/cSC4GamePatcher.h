#pragma once
#include "cIRZGamePatcher.h"
#include <string>

static const uint32_t kPatchCount = 2;
static const std::string szCaption = std::string("SC4Fix r4");

class cSC4GamePatcher : public cRZUnknown, public cIRZGamePatcher
{
	public:
		bool QueryInterface(uint32_t riid, void** ppvObj) {
			if (riid == kGZIID_cIRZGamePatcher) {
				AddRef();
				*ppvObj = static_cast<cIRZGamePatcher*>(this);
				return true;
			}
			else {
				return cRZUnknown::QueryInterface(riid, ppvObj);
			}
		}

		uint32_t AddRef(void) {
			if (dwRefCount == 0) {
				InstallPatches();
			}

			return cRZUnknown::AddRef();
		}

		uint32_t Release(void) {
			if (dwRefCount <= 1) {
				UninstallPatches();
			}

			return cRZUnknown::Release();
		}

	public:
		bool InstallPatches(void) {
			uint32_t dwSuccesses = 0;

			if (PatchTELotCrash()) dwSuccesses++;
			if (PatchTitleBar()) dwSuccesses++;

			if (dwSuccesses == kPatchCount) {
				return true;
			}

			return false;
		}

		bool UninstallPatches(void) {
			uint32_t dwSuccesses = 0;

			if (UnpatchTELotCrash()) dwSuccesses++;
			if (UnpatchTitleBar()) dwSuccesses++;

			if (dwSuccesses == kPatchCount) {
				return true;
			}

			return false;
		}

	protected:
		virtual bool PatchTELotCrash(void) = 0;
		virtual bool PatchTitleBar(void) = 0;

		virtual bool UnpatchTELotCrash(void) = 0;
		virtual bool UnpatchTitleBar(void) = 0;
};