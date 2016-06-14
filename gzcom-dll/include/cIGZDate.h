#pragma once
#include "cIGZUnknown.h"

class cIGZString;
class cRZTime;

class cIGZDate : public cIGZUnknown
{
	public:
		virtual bool Set(uint32_t dwDay, uint32_t dwYear) = 0;
		virtual bool Set(uint32_t dwMonth, uint32_t dwDay, uint32_t dwYear) = 0;
		virtual bool Set(cRZTime const& sTime) = 0;
		virtual bool Set(uint32_t dwDay) = 0;
		virtual bool Set(char const* pszMonthName, uint32_t dwDay, uint32_t dwYear) = 0;

		virtual bool Copy(cIGZDate const& sCopyFrom) = 0;
		virtual bool Clone(cIGZDate** ppCopyTo) = 0;
		
		virtual bool Between(cIGZDate const& sStart, cIGZDate const& sEnd) = 0;
		virtual int32_t CompareTo(cIGZDate const& sOther) = 0;

		virtual uint32_t WeekDay(void) = 0;
		virtual uint32_t Year(void) = 0;
		virtual uint32_t DayOfYear(void) = 0;
		virtual uint32_t DayOfMonth(void) = 0;
		virtual uint32_t FirstDayOfMonth(void) = 0;
		virtual uint32_t FirstDayOfMonth(uint32_t dwMonth) = 0;
		virtual uint32_t Hash(void) = 0; // i.e. Number of days elapsed

		virtual bool IsValid(void) = 0;
		virtual bool Leap(void) = 0;
		virtual bool MaxDate(cIGZDate const& sOther, cIGZDate& sMaxOut) = 0;
		virtual bool MinDate(cIGZDate const& sOther, cIGZDate& sMinOut) = 0;

		virtual uint32_t Month(void) = 0;
		virtual uint32_t Previous(uint32_t dwDayOfPriorWeek, cIGZDate& sOut) = 0;
		virtual uint32_t YearLastTwoDigits(void) = 0;
		virtual uint32_t DayNumber(void) = 0; // Same as Hash

		virtual bool operator<(cIGZDate const& sOther) = 0;
		virtual bool operator<=(cIGZDate const& sOther) = 0;
		virtual bool operator>(cIGZDate const& sOther) = 0;
		virtual bool operator>=(cIGZDate const& sOther) = 0;
		virtual bool operator==(cIGZDate const& sOther) = 0;
		virtual bool operator!=(cIGZDate const& sOther) = 0;

		virtual cIGZDate& operator-(cIGZDate const& sOther) = 0;
		virtual cIGZDate& operator+(cIGZDate const& sOther) = 0;
		
		virtual cIGZDate& operator-(int32_t nDays) = 0;
		virtual cIGZDate& operator+(int32_t nDays) = 0;
		
		virtual cIGZDate& operator++(void) = 0;
		virtual cIGZDate& operator--(void) = 0;
		
		virtual cIGZDate& operator+=(int32_t nDays) = 0;
		virtual cIGZDate& operator-=(int32_t nDays) = 0;

		virtual bool DateString(cIGZString& sDateOut, uint32_t dwFormatID) = 0;
		virtual bool DayWithinMonth(uint32_t dwMonth, uint32_t dwDay, uint32_t dwYear) = 0;
		
		virtual uint32_t DaysInYear(uint32_t dwYear) = 0;
		virtual uint32_t Jday(uint32_t dwMonth, uint32_t dwDay, uint32_t dwYear) = 0;
		virtual bool LeapYear(uint32_t dwYear) = 0;
};