#pragma once
#include "Light.h"

struct SpotLight : public Light {

	SpotLight() {}

	SpotLight(vec4& position, vec4& direction, vec3& color, float intensity) : Light() {

		this->type = spotLight;
		this->position = position;
		this->direction = direction;
		this->color = color;
		this->intensity = intensity;
		this->constantAttenuation = 0.5;
		this->linearAttenuation = 0.01;
		this->quadraticAttenuation = 0.0001;
		this->spotCosCutoff = 0.9;
		this->spotExponent = 4;

	}
	virtual ~SpotLight() {}


	void draw();
};