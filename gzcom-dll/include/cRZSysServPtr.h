#pragma once
#include "cIGZFrameWork.h"
#include "cRZCOMDllDirector.h"

template<class T, uint32_t riid, uint32_t srvid>
class cRZSysServPtr
{
	static_assert(std::is_base_of<cIGZUnknown, T>::value, "T must extend cIGZUnknown");
	public:
		cRZSysServPtr() {
			pService = nullptr;

			cIGZFrameWork* pFrameWork = RZGetFrameWork();
			if (pFrameWork) {
				pFrameWork->GetSystemService(srvid, riid, (void**)&pService);
			}
		}

		virtual ~cRZSysServPtr() {
			if (pService) {
				pService->Release();
			}
		}

		T* operator->() const { return pService; }
		T& operator*() const { return *pService; }
		operator T*() const { return pService; }

	protected:
		T* pService;
};