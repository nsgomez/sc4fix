#include "../include/cRZBaseString.h"
#include <algorithm>
#include <stdarg.h>
#include <stdio.h>

static const uint32_t kRZBaseStringIID = 0xab13a836;

cRZBaseString::cRZBaseString(cIGZString const& szSource)
	: mnRefCount(0), szData(szSource.ToChar()) {
	// Empty
}

cRZBaseString::cRZBaseString(cIGZString const& szSource, size_t dwStart, size_t dwEnd)
	: mnRefCount(0) {
	std::string szNewSource = std::string(szSource.ToChar());
	szData = std::string(szNewSource, dwStart, dwEnd);
}

cRZBaseString::cRZBaseString(char const* pszSource)
	: mnRefCount(0), szData(pszSource) {
	// Empty
}

cRZBaseString::cRZBaseString(char const* pszSource, size_t dwLen)
	: mnRefCount(0), szData(pszSource, dwLen) {
	// Empty
}

cRZBaseString::cRZBaseString(char cChar, size_t dwRepetitions)
	: mnRefCount(0), szData(dwRepetitions, cChar) {
	// Empty
}

cRZBaseString::cRZBaseString(std::string const& szSource)
	: mnRefCount(0), szData(szSource) {
	// Empty
}

cRZBaseString::cRZBaseString(size_t dwStartSize)
	: mnRefCount(0), szData(dwStartSize, '\0') {
	// Empty
}

cRZBaseString::cRZBaseString(void)
	: mnRefCount(0), szData() {
	// Empty
}

bool cRZBaseString::QueryInterface(uint32_t riid, void** ppvObj) {
	switch (riid) {
		case kRZBaseStringIID:
			*ppvObj = static_cast<cRZBaseString*>(this);
			AddRef();
			return true;

		case GZIID_cIGZUnknown:
			*ppvObj = static_cast<cIGZUnknown*>(static_cast<cRZBaseString*>(this));
			AddRef();
			return true;
	}

	return false;
}

uint32_t cRZBaseString::AddRef(void) {
	return ++mnRefCount;
}

uint32_t cRZBaseString::Release(void) {
	if (mnRefCount > 0) {
		--mnRefCount;
	}

	return mnRefCount;
}

uint32_t cRZBaseString::FromChar(char const* pszSource) {
	if (pszSource == nullptr) {
		szData.erase();
	}
	else {
		szData.assign(pszSource);
	}

	return true;
}

uint32_t cRZBaseString::FromChar(char const* pszSource, uint32_t dwLength) {
	if (pszSource == nullptr) {
		szData.erase();
	}
	else {
		szData.assign(pszSource, dwLength);
	}

	return true;
}

char const* cRZBaseString::ToChar(void) const {
	return szData.c_str();
}

char const* cRZBaseString::Data(void) const {
	return szData.c_str();
}

uint32_t cRZBaseString::Strlen(void) const {
	return szData.length();
}

bool cRZBaseString::IsEqual(cIGZString const* szOther, bool bCaseSensitive) const {
	return CompareTo(*szOther, bCaseSensitive) == 0;
}

bool cRZBaseString::IsEqual(cIGZString const& szOther, bool bCaseSensitive) const {
	return CompareTo(szOther, bCaseSensitive) == 0;
}

bool cRZBaseString::IsEqual(char const* pszOther, uint32_t dwLength, bool bCaseSensitive) const {
	return CompareTo(pszOther, dwLength, bCaseSensitive) == 0;
}

int32_t cRZBaseString::CompareTo(cIGZString const& szOther, bool bCaseSensitive) const {
	if (bCaseSensitive) {
		cRZBaseString szThis = cRZBaseString(*this);
		cRZBaseString szOther = cRZBaseString(szOther);

		szThis.MakeUpper();
		szOther.MakeUpper();

		return szThis.CompareTo(szOther, false);
	}
	else {
		return szData.compare(szOther.ToChar());
	}
}

int32_t cRZBaseString::CompareTo(char const* pszOther, uint32_t dwLength, bool bCaseSensitive) const {
	cRZBaseString szOther = cRZBaseString(pszOther, dwLength);
	return CompareTo(szOther, bCaseSensitive);
}

cIGZString& cRZBaseString::operator=(cIGZString const& szOther) {
	char const* pszSource = szOther.ToChar();
	szData = std::string(pszSource);

	return *this;
}

int32_t cRZBaseString::Copy(cIGZString const& szOther) {
	szData = std::string(szOther.ToChar());
	return true;
}

int32_t cRZBaseString::Resize(uint32_t dwNewSize) {
	szData.resize(dwNewSize);
	return true;
}

cIGZString* cRZBaseString::Append(char const* pszOther, uint32_t dwLength) {
	szData.append(pszOther, dwLength);
	return this;
}

cIGZString* cRZBaseString::Append(cIGZString const& szOther) {
	szData.append(szOther.ToChar());
	return this;
}

cIGZString* cRZBaseString::Insert(uint32_t dwPos, char const* pszOther, uint32_t dwLength) {
	szData.insert(dwPos, pszOther, dwLength);
	return this;
}

cIGZString* cRZBaseString::Insert(uint32_t dwPos, cIGZString const& szOther) {
	szData.insert(dwPos, szOther.ToChar());
	return this;
}

cIGZString* cRZBaseString::Replace(uint32_t dwStartPos, char const* pszOther, uint32_t dwLength) {
	szData.replace(dwStartPos, dwLength, pszOther);
	return this;
}

cIGZString* cRZBaseString::Replace(uint32_t dwStartPos, cIGZString const& szOther) {
	szData.replace(dwStartPos, szOther.Strlen(), szOther.ToChar());
	return this;
}

cIGZString* cRZBaseString::Erase(uint32_t dwStartPos, uint32_t dwEndPos) {
	szData.erase(dwStartPos, dwEndPos);
	return this;
}

int32_t cRZBaseString::Find(char const* pszOther, uint32_t dwPos, bool bCaseSensitive) const {
	cRZBaseString szOther = cRZBaseString(pszOther);
	return Find(szOther, dwPos, bCaseSensitive);
}

int32_t cRZBaseString::Find(cIGZString const& szOther, uint32_t dwPos, bool bCaseSensitive) const {
	if (bCaseSensitive) {
		cRZBaseString szThis = cRZBaseString(*this);
		cRZBaseString szOther = cRZBaseString(szOther);

		szThis.MakeUpper();
		szOther.MakeUpper();

		return szThis.Find(szOther, dwPos, false);
	}
	else {
		return szData.find(szOther.ToChar(), dwPos);
	}
}

int32_t cRZBaseString::RFind(char const* pszOther, uint32_t dwPos, bool bCaseSensitive) const {
	cRZBaseString szOther = cRZBaseString(pszOther);
	return RFind(szOther, dwPos, bCaseSensitive);
}

int32_t cRZBaseString::RFind(cIGZString const& szOther, uint32_t dwPos, bool bCaseSensitive) const {
	if (bCaseSensitive) {
		cRZBaseString szThis = cRZBaseString(*this);
		cRZBaseString szOther = cRZBaseString(szOther);

		szThis.MakeUpper();
		szOther.MakeUpper();

		return szThis.RFind(szOther, dwPos, false);
	}
	else {
		return szData.rfind(szOther.ToChar(), dwPos);
	}
}

cIGZString* cRZBaseString::Sprintf(char const* pszFormat, ...) {
	// TODO: Is there a less hacky way of doing this?
	va_list args;
	va_start(args, pszFormat);

	int nBufferSize = vsnprintf(NULL, 0, pszFormat, args);
	char* pszResult = (char*)malloc(nBufferSize + 1);
	vsnprintf(pszResult, nBufferSize, pszFormat, args);
	
	szData.assign(pszResult);
	free(pszResult);

	va_end(args);

	return this;
}

cRZBaseString* cRZBaseString::MakeUpper(void) {
	std::transform(szData.begin(), szData.end(), szData.begin(), ::toupper);
	return this;
}

cRZBaseString* cRZBaseString::MakeLower(void) {
	std::transform(szData.begin(), szData.end(), szData.begin(), ::tolower);
	return this;
}