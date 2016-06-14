#pragma once
#include "cIGZUnknown.h"
#include <list>

class cISC4DisasterInstance;

class cISC4DisasterManager : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual uint32_t GetID(void) = 0;
		
		virtual cISC4DisasterInstance* AttemptDisasterStart(void) = 0;
		virtual cISC4DisasterInstance* AttemptDisasterStart(int32_t nCellX, int32_t nCellZ) = 0;

		virtual bool AddInstanceToList(cISC4DisasterInstance* pInstance) = 0;
		virtual bool RemoveInstanceFromList(cISC4DisasterInstance* pInstance) = 0;

		virtual int32_t GetActiveInstanceCount(void) = 0;
		virtual std::list<cISC4DisasterInstance*> const* GetInstances(void) = 0;
};