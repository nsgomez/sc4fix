#pragma once
#include "cIGZUnknown.h"

class cGZMessage;
class cIGZCheatCodeManager;
class cIGZMessage;
class cIGZString;
class cIGZWin;
class cISC4City;
class cISC4FeatureManager;
class cISC4Nation;
class cISC4Preferences;
class cISC4Region;
class cISC4RegionalCity;
class cISC4RenderProperties;

// Taken from the Mac vtable
class cISC4App : public cIGZUnknown
{
	public:
		virtual bool OnIdle(void) = 0;

		virtual bool RunMessageServerPump(uint32_t dwMinMessages, uint32_t dwMaxMessages, uint32_t dwMaxTime) = 0;
		virtual bool RunMessageServer2Pump(uint32_t dwMinMessages, uint32_t dwMaxMessages, uint32_t dwMaxTime) = 0;
		
		virtual bool RequestNewCity(intptr_t pCity) = 0; // Actually an AutoRefCount<cISC4RegionalCity>
		virtual bool RequestLoadCity(void) = 0;
		virtual bool RequestCloseCity(bool bShowConfirmPrompt) = 0;
		virtual bool RequestSaveCity(bool bShowNotif, bool bUnknown) = 0;
		virtual bool RequestQuit(bool bShowDialog, bool bSaveFirst) = 0;
		virtual bool RequestQuitFromRegion(bool bShowDialog) = 0;
		virtual bool RequestGoToRegionView(bool bShowDialog) = 0;
		
		virtual bool LoadCity(cIGZString& szString, intptr_t pCityOut) = 0; // Actually an AutoRefCount<cISC4RegionalCity>
		virtual bool CloseCity(void) = 0;
		virtual bool SaveCity(bool bUnknown) = 0;
		virtual bool SaveCity(cIGZString const& szName, bool bUnknown) = 0;
		
		virtual bool SavePreferences(void) = 0;
		virtual bool EnableFullGamePauseOnAppFocusLoss(bool bEnable) = 0;

		virtual bool ApplyVideoPreferences(intptr_t const sPreferences) = 0; // Actually takes SC4VideoPreferences const&
		virtual bool GetAutoVideoPreferences(intptr_t pPreferencesOut) = 0; // Actually takes SC4VideoPreferences&

		virtual bool GetDebugFunctionalityEnabled(void) = 0;
		virtual cISC4App* SetDebugFunctionalityEnabled(bool bEnabled) = 0;

		virtual bool GetPopupDialogsEnabled(void) = 0;
		virtual cISC4App* SetPopupDialogsEnabled(bool bEnabled) = 0;

		// All intptr_t types here are actually unspecified class types that have
		// been omitted for simplicity's sake.
		virtual int32_t GetAppState(void) = 0;
		virtual intptr_t GetMainWindow(void) = 0;
		virtual bool GetAppName(cIGZString& szNameOut) = 0;

		virtual bool GetAppIniFileName(cIGZString& szPathOut) = 0;
		virtual bool GetAppIniFilePath(cIGZString& szPathOut) = 0;
		virtual bool GetAppPreferencesFileName(cIGZString& szPathOut) = 0;
		virtual bool GetAppPreferencesFilePath(cIGZString& szPathOut) = 0;

		virtual cISC4FeatureManager* GetFeatureManager(void) = 0;
		virtual cIGZCheatCodeManager* GetCheatCodeManager(void) = 0;
		virtual cISC4Nation* GetNation(void) = 0;
		virtual cISC4Region* GetRegion(void) = 0;
		virtual cISC4RegionalCity* GetRegionalCity(void) = 0;
		virtual cISC4City* GetCity(void) = 0;
		virtual intptr_t GetPreferences(void) = 0; // Returns a cISC4Preferences*
		virtual intptr_t GetNewCitySpecification(void) = 0; // Returns a SC4NewCitySpecification*
		virtual intptr_t GetDebugConsole(void) = 0;
		virtual intptr_t GetGimexFactory(void) = 0; // Returns a cIGZGimexFactory*
		virtual intptr_t GetStringDetokenizer(void) = 0; // Returns a cISCStringDetokenizer*
		virtual intptr_t GetWinLocationSaver(void) = 0; // Returns a cISLWinLocationSaver*
		virtual cISC4RenderProperties* GetRenderProperties(void) = 0;
		virtual intptr_t GetGlyphTextureManager(void) = 0; // Returns a cISC4GlyphTextureManager*
		virtual intptr_t GetLuaInterpreter(void) = 0; // Returns a cIGZLua5*
		virtual intptr_t GetTutorialRegistry(void) = 0; // Returns cSC4TutorialRegistry*

		virtual bool IsRunFirstTimeAfterInstall(void) = 0;
		virtual bool GetAppDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetCDAppDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetDataDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetCDDataDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetPluginDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetCDPluginDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetSkuSpecificDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetUserDataDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetUserPluginDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetRegionsDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetMySimDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetAlbumDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetHTTPCacheDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetTempDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetExceptionReportsDirectory(cIGZString& szPathOut) = 0;
		virtual bool GetTestScriptDirectory(cIGZString& szPathOut) = 0;

		virtual bool AddDynamicLibraryByName(cIGZString const& sName, cIGZString* pBasePath, bool bIgnoreINI) = 0;
		virtual bool AddDynamicLibraryByPath(cIGZString const& sPath, bool bIgnoreINI) = 0;

		typedef bool (*ShutdownCallback)(void*);
		virtual bool RegisterShutdownCallbackFunction(ShutdownCallback pfCallback, void* pUnknown) = 0;
		virtual bool UnregisterShutdownCallbackFunction(ShutdownCallback pfCallback, void* pUnknown) = 0;
};