#pragma once
#include "GameObject.h"

class Butter : public GameObject {
public:
	Butter(vec3& position, Shader* shader)
		: GameObject(position, shader, std::string("objs/butter.obj")) {
	}
	virtual ~Butter() {}

	void update(float timeStep) {}
};