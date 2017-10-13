#pragma once
#include "Light.h"

struct PointLight : public Light {


	PointLight(vec4& position, vec3& color, float intensity) : Light() {
	
		this->type = pointLight;
		this->position = position;
		this->color = color;
		this->intensity = intensity;
		this->constantAttenuation = 0.5;
		this->linearAttenuation = 0.5;
		this->quadraticAttenuation = 0.5;
	
	}
	virtual ~PointLight() {}


	void draw();
};