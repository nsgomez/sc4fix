#pragma once
#include "cIGZUnknown.h"

class cISC4DisasterInstanceVolcano;
class cISC4DisasterManager;
class cISC4Occupant;

class cISC4DisasterManagerVolcano : public cIGZUnknown
{
	public:
		virtual cISC4DisasterManager* AsISC4DisasterManager(void) = 0;

		virtual bool CreateVolcanoInstance(cISC4DisasterInstanceVolcano** ppVolcano) = 0;
		virtual int32_t GetLavaHeightByCityCell(int32_t nCellX, int32_t nCellZ) = 0;
};