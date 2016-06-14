#pragma once

class cS3DVector3
{
	public:
		cS3DVector3(void) {
			fX = 0.0f;
			fY = 0.0f;
			fZ = 0.0f;
		}

		cS3DVector3(float fValue) {
			fX = fValue;
			fY = fValue;
			fZ = fValue;
		}

		cS3DVector3(float fX, float fY, float fZ) {
			this->fX = fX;
			this->fY = fY;
			this->fZ = fZ;
		}

		float Length(void);
		cS3DVector3* Normalize(void);
		cS3DVector3* SetLength(float fNewLength);

		bool operator!=(cS3DVector3 const& sOther);
		bool operator==(cS3DVector3 const& sOther);

		cS3DVector3& operator/=(float fDivisor);

	public:
		float fX, fY, fZ;
};