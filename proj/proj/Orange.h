#pragma once
#include "GameObject.h"
#include "MathHelper.h"
#define edgeX 800
#define edgeZ 600

class Orange : public GameObject {

	float maxSpeed = 300;
	float acceleration = 80;

	int rotationAngle;
	vec3 rotationAxle;

public:
	Orange() {}
	Orange(vec3& position, vec3& speed, int angle, vec3& rotationAxle)
		: GameObject(position, speed, angle), rotationAxle(rotationAxle), rotationAngle(0) {
		model = ModelManager::instance()->getModel("orange");
	}
	virtual ~Orange() {}

	bool outOfBounds();

	void draw();
	void update(float timeStep);
};