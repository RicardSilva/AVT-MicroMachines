#pragma once
#include "GameObject.h"

#include "PointLight.h"

#define LAMP_WIDTH 7.8
#define LAMP_LENGTH 7.8
#define LAMP_HEIGHT 37

class Lamp : public GameObject {

	PointLight light;

public:
	Lamp(vec3& position)
		: GameObject(position, new Hitbox(vec3(position.x - LAMP_LENGTH / 2, position.y - LAMP_HEIGHT / 2, position.z - LAMP_WIDTH / 2),
										vec3(position.x + LAMP_LENGTH / 2, position.y + LAMP_HEIGHT / 2, position.z + LAMP_WIDTH / 2))) {
		model = ModelManager::instance()->getModel("lamp");
		light = PointLight(vec4(position.x, position.y + 36, position.z, 1), vec3(1, 0.0, 0.0), 3);

		if (model == NULL)
			this->isActive = false;
	}
	virtual ~Lamp() {
	}

	void drawLights();
	void draw();
	void update(float timeStep);

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

	void updateHitbox();

};