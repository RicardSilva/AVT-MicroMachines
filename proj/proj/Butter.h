#pragma once
#include "GameObject.h"

class Butter : public GameObject {
public:
	Butter(vec3& position)
		: GameObject(position) {

		model = ModelManager::instance()->getModel("butter");
	}
	virtual ~Butter() {}

	void draw();
	void update(float timeStep) {}
};