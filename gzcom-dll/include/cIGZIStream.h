#pragma once
#include "cIGZUnknown.h"

class cIGZSerializable;
class cIGZString;
class cIGZVariant;

class cIGZIStream : public cIGZUnknown
{
	public:
		virtual bool Skip(uint32_t dwBytes) = 0;

		virtual bool GetSint8(int8_t& cValueOut) = 0;
		virtual bool GetUint8(uint8_t& ucValueOut) = 0;
		virtual bool GetSint16(int16_t& sValueOut) = 0;
		virtual bool GetUint16(uint16_t& usValueOut) = 0;
		virtual bool GetSint32(int32_t& lValueOut) = 0;
		virtual bool GetUint32(uint32_t& ulValueOut) = 0;
		virtual bool GetSint64(int64_t& llValueOut) = 0;
		virtual bool GetUint64(uint64_t& ullValueOut) = 0;
		virtual bool GetFloat32(float& fValueOut) = 0;
		virtual bool GetFloat64(double& dValueOut) = 0;
		virtual bool GetRZCharStr(char* pszDataOut, uint32_t dwMaxBytes) = 0;
		virtual bool GetGZStr(cIGZString& szDataOut) = 0;
		virtual bool GetGZSerializable(cIGZSerializable& sDataOut) = 0;
		virtual bool GetVoid(void* pDataOut, uint32_t dwSize) = 0;

		virtual int32_t GetError(void) = 0;
		virtual int32_t SetUserData(cIGZVariant* pData) = 0;
		virtual int32_t GetUserData(void) = 0;
};