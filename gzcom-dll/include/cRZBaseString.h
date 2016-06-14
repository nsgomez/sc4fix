#pragma once
#include "cIGZString.h"
#include <string>

// This is just our own cIGZString implementation and not necessarily based on
// anything in the game code. SC4's cRZString is more comprehensive, but we
// really just want a reliable, working bare-bones class.
class cRZBaseString : public cIGZString
{
	public:
		cRZBaseString(cIGZString const& szSource);
		cRZBaseString(cIGZString const& szSource, size_t dwStart, size_t dwEnd);
		cRZBaseString(char const* pszSource);
		cRZBaseString(char const* pszSource, size_t dwLen);
		cRZBaseString(char cChar, size_t dwRepetitions);
		cRZBaseString(std::string const& szSource);
		cRZBaseString(size_t dwStartSize);
		cRZBaseString(void);
		virtual ~cRZBaseString(void) { /* Empty */ }

		bool QueryInterface(uint32_t riid, void** ppvObj);
		uint32_t AddRef(void);
		uint32_t Release(void);

		uint32_t FromChar(char const* pszSource);
		uint32_t FromChar(char const* pszSource, uint32_t dwLength);
		char const* ToChar(void) const;
		char const* Data(void) const;

		uint32_t Strlen(void) const;
		bool IsEqual(cIGZString const* szOther, bool bCaseSensitive) const;
		bool IsEqual(cIGZString const& szOther, bool bCaseSensitive) const;
		bool IsEqual(char const* pszOther, uint32_t dwLength, bool bCaseSensitive) const;

		int32_t CompareTo(cIGZString const& szOther, bool bCaseSensitive) const;
		int32_t CompareTo(char const* pszOther, uint32_t dwLength, bool bCaseSensitive) const;

		cIGZString& operator=(cIGZString const& szOther);

		int32_t Copy(cIGZString const& szOther);
		int32_t Resize(uint32_t dwNewSize);

		cIGZString* Append(char const* pszOther, uint32_t dwLength);
		cIGZString* Append(cIGZString const& szOther);
		cIGZString* Insert(uint32_t dwPos, char const* pszOther, uint32_t dwLength);
		cIGZString* Insert(uint32_t dwPos, cIGZString const& szOther);
		cIGZString* Replace(uint32_t dwStartPos, char const* pszOther, uint32_t dwLength);
		cIGZString* Replace(uint32_t dwStartPos, cIGZString const& szOther);
		cIGZString* Erase(uint32_t dwStartPos, uint32_t dwEndPos);

		int32_t Find(char const* pszOther, uint32_t dwPos, bool bCaseSensitive) const;
		int32_t Find(cIGZString const& szOther, uint32_t dwPos, bool bCaseSensitive) const;

		int32_t RFind(char const* pszOther, uint32_t dwPos, bool bCaseSensitive) const;
		int32_t RFind(cIGZString const& szOther, uint32_t dwPos, bool bCaseSensitive) const;

		cIGZString* Sprintf(char const* pszFormat, ...);

		cRZBaseString* MakeUpper(void);
		cRZBaseString* MakeLower(void);

	protected:
		std::string szData;
		uint32_t mnRefCount;
};