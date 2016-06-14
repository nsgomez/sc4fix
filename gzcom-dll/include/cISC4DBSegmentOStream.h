#pragma once
#include "cIGZOStream.h"

class cGZPersistResourceKey;
class cIGZSerializable;
class cIGZVariant;
class cISC4DBSegment;

class cISC4DBSegmentOStream : public cIGZOStream
{
	public:
		virtual bool Open(cISC4DBSegment* pSegment, cGZPersistResourceKey const& sKey, bool bUnknown) = 0;
		virtual bool Close(void) = 0;

		virtual bool IsOpen(void) = 0;
		
		virtual int32_t GetRecord(void) = 0;
		virtual int32_t GetSegment(void) = 0;
		
		virtual bool WriteGZSerializable(cIGZSerializable const* pSegment) = 0;
		virtual bool WriteResKey(cGZPersistResourceKey const& sKey) = 0;
		virtual bool WriteVariant(cIGZVariant const& sVariant) = 0;
};