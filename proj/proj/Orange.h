#pragma once
#include "GameObject.h"
class Orange : public GameObject {
public:
	Orange(vec3& position)
		: GameObject(position) {
		model = ModelManager::instance()->getModel("orange");
	}
	virtual ~Orange() {}

	void update(float timeStep) {}
};