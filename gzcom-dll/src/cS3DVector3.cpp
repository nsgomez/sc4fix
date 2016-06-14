#include "cS3DVector3.h"
#include <math.h>

float cS3DVector3::Length(void) {
	float fX2 = fX * fX;
	float fY2 = fY * fY;
	float fZ2 = fZ * fZ;

	return sqrtf(fX2 + fY2 + fZ2);
}

cS3DVector3* cS3DVector3::Normalize(void) {
	float fLength = Length();
	float fMultiplier = 0.0f;

	if (fLength > 0.0f) {
		fMultiplier = 1 / fLength;
	}

	fX *= fMultiplier;
	fY *= fMultiplier;
	fZ *= fMultiplier;

	return this;
}

cS3DVector3* cS3DVector3::SetLength(float fNewLength) {
	float fLength = Length();
	if (fLength > 0.0f) {
		float fMultiplier = fNewLength / fLength;

		fX *= fMultiplier;
		fY *= fMultiplier;
		fZ *= fMultiplier;
	}

	return this;
}

bool cS3DVector3::operator!=(cS3DVector3 const& sOther) {
	return !(operator==(sOther));
}

bool cS3DVector3::operator==(cS3DVector3 const& sOther) {
	float fDiffX = fabs(sOther.fX - fX);
	float fDiffY = fabs(sOther.fY - fY);
	float fDiffZ = fabs(sOther.fZ - fZ);

	return fDiffX <= 0.0001 && fDiffY <= 0.0001 && fDiffZ <= 0.0001;
}

cS3DVector3& cS3DVector3::operator/=(float fDivisor) {
	float fMultiplier = 1 / fDivisor;
	fX *= fMultiplier;
	fY *= fMultiplier;
	fZ *= fMultiplier;

	return *this;
}