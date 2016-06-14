#pragma once
#include "cIGZCOMLibrary.h"
#include "cRZBaseString.h"
#include <string>

class cIGZCOMDirector;

// This class is derived from Paul Pedriana's released code and should be perfect
// aside from the cRZBaseString substitution made in place for cRZString.
class cGZCOMLibrary : public cIGZCOMLibrary
{
	public:
		typedef void* GZLibraryHandle;

		cGZCOMLibrary(void);
		cGZCOMLibrary(const cIGZString& sLibraryPath);
		virtual ~cGZCOMLibrary(void);

		bool QueryInterface(uint32_t riid, void** ppvObj);
		uint32_t AddRef(void);
		uint32_t Release(void);

		bool Load(void);
		bool Free(void);

		void GetPath(cIGZString& sPath) const;
		bool SetPath(const cIGZString& sPath);

		GZLibraryHandle GetHandle() const;
		void SetHandle(GZLibraryHandle handle);

		cIGZCOMDirector* GetDirector(void) const;
		void SetDirector(cIGZCOMDirector* pDirector);

		bool IsLoaded() const;
		void SetLoaded(bool bUse);

		bool operator< (const cGZCOMLibrary& rhs) const;
		bool operator> (const cGZCOMLibrary& rhs) const;
		bool operator== (const cGZCOMLibrary& rhs) const;

	protected:
		bool mbLoaded;
		uint32_t mnRefCount;
		cIGZCOMDirector* mpDirector;
		cRZBaseString msLibraryPath;
		GZLibraryHandle mHandle;
};