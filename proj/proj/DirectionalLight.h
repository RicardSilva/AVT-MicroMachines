#pragma once

#include "Light.h"
#include "vec3.h"

struct DirectionalLight : public Light {
	
	void draw();

	DirectionalLight() {}
	DirectionalLight(vec3& direction, vec3& color) : Light(direction, color) {}

};