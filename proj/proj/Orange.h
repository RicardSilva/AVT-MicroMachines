#pragma once
#include "GameObject.h"
#define edgeX 650
#define edgeZ 450
class Orange : public GameObject {
	vec3 speed;
	vec3 trajectory;
	float absSpeed=0;
	int angle=std::rand() % 360;
	float speedCap = 1500;
	float acceleration = 10;
public:
	Orange(vec3& position)
		: GameObject(position) {
		model = ModelManager::instance()->getModel("orange");
	}
	virtual ~Orange() {}
	void reset();
	bool outOfBounds();
	int getAngle() { return angle; }
	void draw();
	void update(float timeStep);
};