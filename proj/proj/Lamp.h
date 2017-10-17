#pragma once
#include "GameObject.h"

#include "PointLight.h"
class Lamp : public GameObject {

	PointLight light;

public:
	Lamp(vec3& position)
		: GameObject(position) {
		model = ModelManager::instance()->getModel("lamp");
		light = PointLight(vec4(position.x, position.y + 25, position.z, 1), vec3(0.5, 0.5, 0.3), 1);

		if (model == NULL)
			this->isActive = false;
	}
	virtual ~Lamp() {
	}

	void drawLights();
	void draw();
	void update(float timeStep) {}

	void toogleLight() {
		if (light.isActive) {
			light.isActive = false;
			shader->decActiveLights();
		}
		else {
			light.isActive = true;
			shader->incActiveLights();
		}

	}

};