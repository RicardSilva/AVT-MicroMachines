#pragma once

#include "Light.h"
#include "vec3.h"

struct DirectionalLight : public Light {
	
	void draw();

	DirectionalLight() {}
	DirectionalLight(vec4& direction, vec3& color, float intensity) : Light() {
		this->type = directionalLight;
		this->direction = direction;
		this->color = color;
		this->intensity = intensity;
	}

};