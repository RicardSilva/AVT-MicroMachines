#include "Camera.h"

void Camera::computeView() {
	loadIdentity(VIEW);
	lookAt(eye, target, up);
}

void Camera::computeCarCameraPosition(const vec3& pos, int angle) {
	double x, y, z;

	x = pos.x; // aim for the car's center of rotation
	y = pos.y;
	z = pos.z;

	target = vec3(x, y, z);

	x = x - (50 * sin(angle * 3.14 / 180));
	y = y + 30;
	z = z - (50 * cos(angle * 3.14 / 180));

	eye = vec3(x, y, z);
}