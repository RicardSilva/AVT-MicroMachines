#pragma once
#include "GameObject.h"
#include "MathHelper.h"


#define edgeX 800
#define edgeZ 600
#define ORANGE_RADIUS 15

class Orange : public GameObject {

	float maxSpeed = 300;
	float acceleration = 80;

	int rotationAngle;
	vec3 rotationAxle;

public:
	Orange() {}
	Orange(vec3& position, vec3& speed, int angle, vec3& rotationAxle)
		: GameObject(position, speed, angle, "orange", new Hitbox(vec3(position.x - ORANGE_RADIUS, position.y - ORANGE_RADIUS + 30, position.z - ORANGE_RADIUS),
													vec3(position.x + ORANGE_RADIUS, position.y + ORANGE_RADIUS + 30, position.z + ORANGE_RADIUS))),
			rotationAxle(rotationAxle), rotationAngle(0)
	{ }

	virtual ~Orange() {}

	bool outOfBounds();
	void increaseSpeed();
	void draw();
	void update(float timeStep);

	void updateHitbox();
};