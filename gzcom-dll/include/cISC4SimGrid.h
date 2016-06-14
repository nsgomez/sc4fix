#pragma once
#include "cIGZUnknown.h"

template<typename T>
class cISC4SimGrid : public cIGZUnknown
{
	public:
		virtual bool Init(void) = 0;
		virtual bool Shutdown(void) = 0;

		virtual uint32_t GetInstanceID(void) = 0;
		virtual bool SetInstanceID(uint32_t dwInstanceID) = 0;

		virtual T GetCellValue(int32_t nCellX, int32_t nCellZ) = 0;
		virtual T GetAverageValueInCellRect(int32_t nTopLeftX, int32_t nTopLeftZ, int32_t nBottomRightX, int32_t nBottomRightZ) = 0;

		virtual bool SetTractSize(int32_t nSize) = 0;
		virtual int32_t GetTractSize(void) = 0;
		
		virtual int32_t GetTractShift(void) = 0;
		
		virtual int32_t GetTractCountX(void) = 0;
		virtual int32_t GetTractCountZ(void) = 0;
		
		virtual float GetTractWidthX(void) = 0;
		virtual float GetTractWidthZ(void) = 0;
		
		virtual float GetOneOverTractWidthX(void) = 0;
		virtual float GetOneOverTractWidthZ(void) = 0;

		virtual bool TractIsInBounds(uint32_t dwTractX, uint32_t dwTractZ) = 0;
		virtual bool PositionToTract(float fPosX, float fPosZ, int32_t& nTractX, int32_t& nTractZ) = 0;
		virtual bool TractCornerToPosition(int32_t nTractX, int32_t nTractZ, float& fPosX, float& fPosZ) = 0;
		virtual bool TractCenterToPosition(int32_t nTractX, int32_t nTractZ, float& fPosX, float& fPosZ) = 0;

		virtual T GetTractValue(int32_t nTractX, int32_t nTractZ) = 0;
		virtual T GetAverageValueInTractRect(int32_t nTopLeftX, int32_t nTopLeftZ, int32_t nBottomRightX, int32_t nBottomRightZ) = 0;

		virtual intptr_t GetGridData(void) = 0;

		virtual bool SetTractValue(int32_t nTractX, int32_t nTractZ, T value) = 0;
		virtual bool SetTractValues(T value) = 0;
};