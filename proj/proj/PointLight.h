#pragma once
#include "Light.h"

struct PointLight : public Light {

	PointLight() {}

	PointLight(vec4& position, vec3& color, float intensity) : Light() {
	
		this->type = pointLight;
		this->position = position;
		this->color = color;
		this->intensity = intensity;
		this->constantAttenuation = 0.5;
		this->linearAttenuation = 0.001;
		this->quadraticAttenuation = 0.00001;
	
	}
	virtual ~PointLight() {}


	void draw();
};