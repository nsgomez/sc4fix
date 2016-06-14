#pragma once
#include "cIGZUnknown.h"

class cISC4DisasterInstance;

class cISC4DisasterInstanceVolcano : public cIGZUnknown
{
	public:
		virtual cISC4DisasterInstance* AsISC4DisasterInstance(void) = 0;
		virtual cISC4DisasterInstance* AsISC4DisasterInstance2(void) = 0;
		
		virtual bool SetLocation(int32_t nCellX, int32_t nCellZ) = 0;
		virtual int32_t GetLavaHeightByCityCell(int32_t nCellX, int32_t nCellZ) = 0;
		
		virtual int32_t GetState(void) = 0;
		virtual bool SetState(int32_t nState) = 0;
};