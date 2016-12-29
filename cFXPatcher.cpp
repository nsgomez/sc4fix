#include "cFXPatcher.h"
#include "cFXDisconnectorPatch.h"
#include "cFXFaunaControllerPatch.h"
#include "cFXMMPCyclePatch.h"
#include "cFXPuzzlePieceTEPatch.h"

#define SC4FIX_VERSION_MAJOR 1
#define SC4FIX_VERSION_MINOR 0
#define SC4FIX_VERSION_PATCH 0
#define SC4FIX_VERSION_BUILD 0

bool cFXPatcher::InstallPatches(bool bUseSteamPatches) {
	return true;
}

bool cFXPatcher::UninstallPatches(void) {
	return true;
}

const patchv cFXPatcher::GetVersion(void) const {
	static patchv ver;
	ver.vtype.major = SC4FIX_VERSION_MAJOR;
	ver.vtype.minor = SC4FIX_VERSION_MINOR;
	ver.vtype.patch = SC4FIX_VERSION_PATCH;
	ver.vtype.build = SC4FIX_VERSION_BUILD;

	return ver;
}