#pragma once

#include "vec3.h"
#include "ShaderManager.h"
#include "Shader.h"

enum lightType { directionalLight, pointLight, spotLight };

struct Light {

	Shader* shader;

	bool isActive = true;
	lightType type;

	vec4 position;
	vec4 direction;
	vec3 color;
	float intensity;

	float constantAttenuation;
	float linearAttenuation;
	float quadraticAttenuation;

	float spotCosCutoff;
	float spotExponent;

	Light() {
		shader = ShaderManager::instance()->getShader("lightShader");
	}

	virtual void draw() = 0;
};