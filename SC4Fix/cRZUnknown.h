#pragma once
#include <cIGZUnknown.h>

class cRZUnknown : public cIGZUnknown
{
	public:
		cRZUnknown(void) {
			dwRefCount = 0;
		}

		bool QueryInterface(uint32_t riid, void** ppvObj) {
			if (riid == 1) {
				AddRef();
				*ppvObj = static_cast<cIGZUnknown*>(this);
				return true;
			}
			else {
				return false;
			}
		}

		uint32_t AddRef(void) {
			dwRefCount++;
			return dwRefCount;
		}

		uint32_t Release(void) {
			if (dwRefCount > 0) {
				dwRefCount--;
			}

			if (dwRefCount == 0) {
				delete this;
				return 0;
			}
			else {
				return dwRefCount;
			}
		}

	protected:
		uint32_t dwRefCount;
};