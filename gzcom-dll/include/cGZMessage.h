#pragma once
#include <stdint.h>

class cGZMessage
{
	public:
		cGZMessage(uint32_t dwMessageType) {
			this->dwMessageType = dwMessageType;
			this->dwData1 = 0;
			this->dwData2 = 0;
			this->dwData3 = 0;
		}

		uint32_t dwMessageType;
		uint32_t dwData1;
		uint32_t dwData2;
		uint32_t dwData3;
};