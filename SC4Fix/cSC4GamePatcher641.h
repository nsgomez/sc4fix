#pragma once
#include "cSC4GamePatcher.h"

class cSC4GamePatcher641 : public cSC4GamePatcher
{
	protected:
		bool PatchTELotCrash(void);
		bool PatchTitleBar(void);

		bool UnpatchTELotCrash(void);
		bool UnpatchTitleBar(void);

	protected:
		static void Hook_Sub96D8E9(void);
		static void Hook_Sub65EBA0(void);
		static void Hook_Sub65EBA0_Pt2(void);

		static void Hook_Steam_Sub44C2B0(void);

	private:
		uint8_t wTEPatchBytes_96D8E9[5];
		uint8_t wTEPatchBytes_65EBA0[5];
		uint8_t wTitlePatchBytes[5];
};