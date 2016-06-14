#pragma once
#include "cIGZUnknown.h"

class cIGZRadioStation;
class cIGZString;

class cIGZRadio : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;
		virtual bool OnIdle(void) = 0;

		virtual int32_t GetRadioSound(void) = 0;

		virtual bool PlaySong(cIGZString const& sSongName) = 0;
		virtual bool PlayNextSong(bool bUnknown) = 0;

		virtual bool GetCurrentStation(uint32_t& dwStationID) = 0;
		virtual bool GetCurrentStation(char* pszStationName) = 0;

		virtual cIGZRadioStation* GetStation(uint32_t dwStationID) = 0;
		virtual bool SetStation(uint32_t dwStationID) = 0;

		virtual cIGZRadioStation* GetStation(char const* pszStationName) = 0;
		virtual bool SetStation(char const* pszStationName, intptr_t* pFadeOptions) = 0;
		
		virtual int32_t GetVolume(void) = 0;
		virtual bool SetVolume(int32_t nVolume) = 0;

		virtual int32_t GetStationCount(void) = 0;

		virtual bool IsStationAvailable(char const* pszStationName) = 0;
		virtual bool AddStation(cIGZRadioStation* pStation) = 0;
		virtual bool RemoveStation(cIGZRadioStation* pStation, bool bRelease) = 0;
		virtual bool RemoveStation(char const* pszStationName, bool bRelease) = 0;
		virtual bool RemoveAllStations(bool bRelease) = 0;

		virtual bool TurnOn(bool bToggle) = 0;
		virtual bool IsOn(void) = 0;
		virtual bool Mute(bool bToggle) = 0;

		virtual int32_t GetOption(int32_t nRadioOption) = 0;
		virtual bool SetOption(int32_t nRadioOption) = 0;

		virtual bool GetRadioDirectory(cIGZString& sPath) = 0;
		virtual bool SetRadioDirectory(cIGZString const& sPath) = 0;

		virtual bool SetOnDemandState(bool bState) = 0;

		virtual bool StopPlayback(void) = 0;

		virtual bool GetCurrentSong(cIGZString& sSongName) = 0;
		virtual bool SetCurrentSong(cIGZString const& sSongName) = 0;

		virtual bool IsPlaying(void) = 0;

		virtual bool ReadSettings(intptr_t pRadioSettings) = 0;
		virtual bool WriteSettings(intptr_t pRadioSettings) = 0;

};