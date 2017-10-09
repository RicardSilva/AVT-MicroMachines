#pragma once

#include "vec3.h"
#include "ShaderManager.h"
#include "Shader.h"

struct Light {

	Shader* shader;


	vec3 position;
	vec3 direction;
	vec3 color;
	float intensity;

	Light() {
		shader = ShaderManager::instance()->getShader("lightShader");
	}
	Light(vec3& direction, vec3& color) : direction(direction), color(color) {
		shader = ShaderManager::instance()->getShader("lightShader");
	}

	virtual void draw() = 0;
};