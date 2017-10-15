#pragma once
#include "vec3.h"
#include "AVTmathLib.h"
#include "GameObject.h"

#define PI 3.14

#define WHEEL_OUTER 4.0
#define CAR_WIDTH 4.0
#define CAR_LENGTH 4.0
#define CAR_HEIGHT 4.0
#define DISTANCE_BETWEEN_AXLES 4.0

class Car : public GameObject {
	
public:
	// Input flags
	bool turnLeft = false;
	bool turnRight = false;
	bool goForward = false;
	bool goBack = false;

private:
	// Car physics
	float angleInc = 3;
	float maxSpeed = 325;
	float maxBackwardsSpeed = -100;

	float acceleration = 150;
	float backwardsAcceleration = 200;
	float inercia = 175;
	
	

public:
	Car(vec3& position)  //TODO
		: GameObject(position, new Hitbox(vec3(position.x - CAR_WIDTH / 2.0 + DISTANCE_BETWEEN_AXLES / 2.0, position.y - CAR_LENGTH / 2, position.z - WHEEL_OUTER),
			vec3(position.x + CAR_WIDTH / 2.0 + DISTANCE_BETWEEN_AXLES / 2.0, position.y + CAR_LENGTH / 2.0, position.z + CAR_HEIGHT))) {
		model = ModelManager::instance()->getModel("car");
		if (model == NULL)
			this->isActive = false;
		
	}
	virtual ~Car() {}
	int getAngle() { return angle; }

	void drawLights();
	virtual void draw();
	void update(float timeStep);
	void updateHitbox();

};
