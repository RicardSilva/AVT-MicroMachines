#pragma once
#include "GameObject.h"

#define BUTTER_WIDTH 18
#define BUTTER_LENGTH 20
#define BUTTER_HEIGHT 40

class Butter : public GameObject {
	float inercia = 350;
public:

	Butter(vec3& position)
		: GameObject(position, new Hitbox(vec3(position.x - BUTTER_WIDTH / 2.0, position.y - BUTTER_LENGTH / 2.0, position.z - BUTTER_HEIGHT / 2),
										vec3(position.x + BUTTER_WIDTH / 2.0, position.y + BUTTER_LENGTH / 2.0, position.z + BUTTER_HEIGHT / 2))) {

		model = ModelManager::instance()->getModel("butter");

		if (model == NULL)
			this->isActive = false;
	}
	virtual ~Butter() {}

	void draw();
	void update(float timeStep);

	void updateHitbox();
};