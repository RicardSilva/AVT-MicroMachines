#pragma once
#include "vec3.h"
#include "AVTmathLib.h"
#include "GameObject.h"

#define PI 3.14

class Car : public GameObject {
	
	vec3 speed;
	int angle;
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
	Car(vec3& position) 
		: GameObject(position) {
		model = ModelManager::instance()->getModel("car");
		
	}
	virtual ~Car() {}
	int getAngle() { return angle; }

	virtual void draw();
	void update(float timeStep);


};
