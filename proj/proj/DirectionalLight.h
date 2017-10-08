#pragma once

#include "Light.h"
#include "vec3.h"

struct DirectionalLight : public Light {

	vec3 direction;

	void draw();

	DirectionalLight() : Light() {}

};