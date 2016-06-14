#pragma once
#include "cIGZUnknown.h"

class cIGZString;
class cIGZUnknownList;
class cIGZVariant;
class cISCProperty;

class cISCPropertyHolder : public cIGZUnknown
{
	public:
		virtual bool HasProperty(uint32_t dwProperty) = 0;
		
		virtual bool GetPropertyList(cIGZUnknownList** ppList) = 0;
		virtual cISCProperty* GetProperty(uint32_t dwProperty) = 0;
		virtual bool GetProperty(uint32_t dwProperty, uint32_t& dwValueOut) = 0;
		virtual bool GetProperty(uint32_t dwProperty, cIGZString& szValueOut) = 0;
		virtual bool GetProperty(uint32_t dwProperty, uint32_t riid, void** ppvObj) = 0;
		virtual bool GetProperty(uint32_t dwProperty, void* pUnknown, uint32_t& dwUnknownOut) = 0;

		virtual bool AddProperty(cISCProperty* pProperty, bool bUnknown) = 0;
		virtual bool AddProperty(uint32_t dwProperty, cIGZVariant const* pVariant, bool bUnknown) = 0;
		virtual bool AddProperty(uint32_t dwProperty, uint32_t dwUnknown, bool bUnknown) = 0;
		virtual bool AddProperty(uint32_t dwProperty, cIGZString const& szValue) = 0;
		virtual bool AddProperty(uint32_t dwProperty, int32_t lUnknown, bool bUnknown) = 0;
		virtual bool AddProperty(uint32_t dwProperty, void* pUnknown, uint32_t dwUnknown, bool bUnknown) = 0;

		virtual bool CopyAddProperty(cISCProperty* pProperty, bool bUnknown) = 0;

		virtual bool RemoveProperty(uint32_t dwProperty) = 0;
		virtual bool RemoveAllProperties(void) = 0;

		typedef void (*FunctionPtr1)(cISCProperty*, void*);
		typedef bool (*FunctionPtr2)(cISCProperty*, void*);

		virtual bool EnumProperties(FunctionPtr1 pFunction1, void* pUnknown) = 0;
		virtual bool EnumProperties(FunctionPtr2 pFunction2, FunctionPtr1 pFunctionPipe) = 0;

		virtual bool CompactProperties(void) = 0;
};