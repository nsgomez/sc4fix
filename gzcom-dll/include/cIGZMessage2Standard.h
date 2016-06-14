#pragma once
#include "cIGZMessage2.h"

class cIGZSerializable;
class cIGZString;

class cIGZMessage2Standard : public cIGZMessage2
{
	public:
		virtual bool GetHasData1(void) = 0;
		virtual int32_t GetData1(void) = 0;
		virtual void* GetVoid1(void) = 0;

		virtual cIGZMessage2Standard* SetData1(int32_t ulData) = 0;
		virtual cIGZMessage2Standard* SetVoid1(void* pData) = 0;

		virtual bool GetHasData2(void) = 0;
		virtual int32_t GetData2(void) = 0;
		virtual void* GetVoid2(void) = 0;

		virtual cIGZMessage2Standard* SetData2(int32_t ulData) = 0;
		virtual cIGZMessage2Standard* SetVoid2(void* pData) = 0;

		virtual bool GetHasData3(void) = 0;
		virtual int32_t GetData3(void) = 0;
		virtual void* GetVoid3(void) = 0;

		virtual cIGZMessage2Standard* SetData3(int32_t ulData) = 0;
		virtual cIGZMessage2Standard* SetVoid3(void* pData) = 0;

		virtual bool GetHasData4(void) = 0;
		virtual int32_t GetData4(void) = 0;
		virtual void* GetVoid4(void) = 0;

		virtual cIGZMessage2Standard* SetData4(int32_t ulData) = 0;
		virtual cIGZMessage2Standard* SetVoid4(void* pData) = 0;

		virtual bool GetHasString(void) = 0;
		virtual bool GetString(uint32_t dwMaxLen, void** ppStringOut) = 0;
		virtual bool SetString(cIGZString* pString) = 0;

		virtual bool GetHasIGZUnknown(void) = 0;
		virtual cIGZUnknown* GetIGZUnknown(void) = 0;
		virtual bool SetIGZUnknown(cIGZUnknown* pObj) = 0;

		virtual bool GetHasExtra(void) = 0;
		virtual uint32_t GetExtra(uint32_t dwLen, void** ppOut) = 0;
		virtual bool SetExtra(cIGZSerializable* pSerializable) = 0;
};