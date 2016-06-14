#pragma once
#include "cIGZUnknown.h"

class cIGZIStream;
class cIGZOStream;

class cIGZSerializable : public cIGZUnknown
{
	public:
		virtual int32_t Write(cIGZOStream& gzOut) = 0;
		virtual int32_t Read(cIGZIStream& gzIn) = 0;
		virtual int32_t GetGZCLSID(void) = 0;
};