#include "cFXManager.h"
#include "version.h"

cFXManager::cFXManager(void) :
	m_pCurPatcher(NULL),
	m_bHasValidVersion(false),
	m_bRunningSteam(false) { }

cFXManager::~cFXManager(void) {
	if (m_pCurPatcher != NULL) {
		UnloadCurrentPatcher();
	}
}

bool cFXManager::LoadPatcher(cIFXPatcher* pPatcher) {
	if (pPatcher == NULL) {
		return false;
	}
	
	uint32_t dwNewPatchVer = pPatcher->GetVersion().dw;
	uint32_t dwCurPatchVer = GetCurrentPatcherVersion().dw;

	if (dwNewPatchVer <= dwCurPatchVer) {
		return false;
	}
	else if (IsPatcherLoaded() && !UnloadCurrentPatcher()) {
		return false;
	}

	pPatcher->AddRef();
	m_pCurPatcher = pPatcher;

	if (!pPatcher->InstallPatches(IsSteamVersion())) {
		MessageBoxA(NULL, "SC4Fix Warning",
			"The SC4Fix patcher reported an error applying patches and may not be effective.",
			MB_OK | MB_ICONASTERISK);
	}

	return true;
}

bool cFXManager::UnloadCurrentPatcher(void) {
	if (!IsPatcherLoaded()) {
		return false;
	}

	m_pCurPatcher->UninstallPatches();
	m_pCurPatcher->Release();
	m_pCurPatcher = NULL;

	return true;
}

bool cFXManager::IsPatcherLoaded(void) {
	return (m_pCurPatcher != NULL);
}

patchv cFXManager::GetCurrentPatcherVersion(void) {
	if (m_pCurPatcher == NULL) {
		patchv verZero;
		verZero.dw = 0;

		return verZero;
	}
	else {
		return m_pCurPatcher->GetVersion();
	}
}

bool cFXManager::IsSteamVersion(void) {
	return (GetGameVersion() == 641);
}

bool cFXManager::Init(void) {
	DetermineGameVersion();
	switch (GetGameVersion()) {
		case 610:
			HandleVersion610Or613();
			break;

		case 638:
			HandleVersion638();
			break;

		case 640:
			m_bHasValidVersion = true;
			break;

		case 641:
			m_bRunningSteam = true;
			m_bHasValidVersion = true;
			break;

		default:
			HandleUnknownVersion();
			break;
	}
	
	return true;
}

bool cFXManager::Shutdown(void) { return true; }
bool cFXManager::OnTick(void) { return true; }
bool cFXManager::OnIdle(void) { return true; }
int32_t cFXManager::GetServicePriority(void) { return 0; }
uint32_t cFXManager::GetServiceID(void) { return 0x5C4F1810; }

bool cFXManager::IsServiceRunning(void) {
	return m_bHasValidVersion;
}

cIGZSystemService* cFXManager::SetServiceRunning(bool bRunning) {
	return static_cast<cIGZSystemService*>(this);
}

cIGZSystemService* cFXManager::SetServiceID(uint32_t dwServiceId) {
	return static_cast<cIGZSystemService*>(this);
}