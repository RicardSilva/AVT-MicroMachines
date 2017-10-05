#pragma once
#include "GameObject.h"
class Orange : public GameObject {
public:
	Orange(vec3& position, Shader* shader)
		: GameObject(position, shader, std::string("objs/orange.obj")) {
	}
	virtual ~Orange() {}

	void update(float timeStep) {}
};