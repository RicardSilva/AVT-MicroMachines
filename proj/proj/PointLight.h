#pragma once
#include "Light.h"

struct PointLight : public Light {

	PointLight() {}

	PointLight(vec4& position, vec3& color, float intensity) : Light() {
	
		this->type = pointLight;
		this->position = position;
		this->color = color;
		this->intensity = intensity;
		this->constantAttenuation = 0.0;
		this->linearAttenuation = 0.005;
		this->quadraticAttenuation = 0.0005;
	
	}
	virtual ~PointLight() {}


	void draw();
};