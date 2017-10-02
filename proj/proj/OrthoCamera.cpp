#include "OrthoCamera.h"

void OrthoCamera::computeProjection(int w, int h) {

	loadIdentity(PROJECTION);
	float ratio = (float)w / h;
	if (w <= h)
		ortho(left, right, bottom / ratio, top / ratio, nearp, farp);
	else
		ortho(left * ratio, right * ratio, bottom, top, nearp, farp);

	
}