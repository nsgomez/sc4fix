#pragma once
#include <stdint.h>

class cRZPoint
{
	public:
		union
		{
			int32_t nX;
			float fX;
		};

		union
		{
			int32_t nY;
			float fY;
		};
};