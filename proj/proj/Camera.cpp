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

	x = x - (60 * cos(angle * 3.14 / 180));
	y = y + 25;
	z = z - (60 * -sin(angle * 3.14 / 180));

	eye = vec3(x, y, z);
}
void Camera::computeCockpitCameraPosition(const vec3& pos, int angle) {
	double x, y, z;

	x = pos.x - (4.5 * cos(angle * 3.14 / 180)); // camera inside car
	y = pos.y + 10;
	z = pos.z - (4.5 * -sin(angle * 3.14 / 180));

	eye = vec3(x, y, z);

	x = x + (50 * cos(angle * 3.14 / 180));
	y = y;
	z = z + (50 * -sin(angle * 3.14 / 180));

	target = vec3(x, y, z);
}
void Camera::computeBackCameraPosition(const vec3& pos, int angle) {
	double x, y, z;

	x = pos.x - (4.5 * cos(angle * 3.14 / 180)); // camera inside car
	y = pos.y + 10;
	z = pos.z - (4.5 * -sin(angle * 3.14 / 180));

	eye = vec3(x, y, z);

	x = x - (50 * cos(angle * 3.14 / 180));
	y = y - 9;
	z = z - (50 * -sin(angle * 3.14 / 180));

	target = vec3(x, y, z);
}

vec2 Camera::convertWorldToScreenSpace(vec3 worldPosition) {
	vec4 coords = vec4(worldPosition, 1.0f);
	coords = multMatrixPoint(VIEW, coords);
	coords = multMatrixPoint(PROJECTION, coords);

	if (coords.w <= 0)
		return vec2(-1, -1);

	float x = (coords.x / coords.w + 1) / 2.0f;
	float y = 1 - ((coords.y / coords.w + 1) / 2.0f);


	return vec2(x, y);
}