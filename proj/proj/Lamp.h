#pragma once
#include "GameObject.h"

#include "PointLight.h"

#define LAMP_WIDTH 7.8
#define LAMP_LENGTH 7.8
#define LAMP_HEIGHT 37

class Lamp : public GameObject {

	PointLight light;
	float inercia = 370;

public:
	Lamp(vec3& position)
		: GameObject(position, "lamp", new Hitbox(vec3(position.x - LAMP_LENGTH / 2, position.y - LAMP_HEIGHT / 2, position.z - LAMP_WIDTH / 2),
										vec3(position.x + LAMP_LENGTH / 2, position.y + LAMP_HEIGHT / 2, position.z + LAMP_WIDTH / 2))),
		light(PointLight(vec4(position.x, position.y + 35, position.z, 1), vec3(0.5, 0.5, 0.3), 0.8))
	{ }

	virtual ~Lamp() {
	}

	void drawLights();
	void draw();
	void update(float timeStep);

	void toogleLight() {
		if (light.isActive) {
			light.isActive = false;
		}
		else {
			light.isActive = true;
		}

	}

	void updateHitbox();

	void updateLight(vec3 pos);

};