#pragma once
#include "vec3.h"
#include "AVTmathLib.h"
#include "GameObject.h"
#include "SpotLight.h"
#include "MathHelper.h"

#define PI 3.14

#define CAR_WIDTH 16.2
#define CAR_LENGTH 30
#define CAR_HEIGHT 11.7

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

	SpotLight leftLight;
	SpotLight rightLight;
	
	

public:
	Car(vec3& position)
		: GameObject(position, new Hitbox(vec3(position.x - CAR_LENGTH / 2, position.y - CAR_HEIGHT / 2, position.z - CAR_WIDTH / 2),
										vec3(position.x + CAR_LENGTH / 2, position.y + CAR_HEIGHT / 2, position.z + CAR_WIDTH / 2))),
		leftLight(SpotLight(vec4(position + vec3(14.4, 20, -4.60), 1), vec4(1, 0, 0, 0), vec3(1, 1, 1), 1)),
		rightLight(SpotLight(vec4(position + vec3(14.4, 20, 4.60), 1), vec4(1, 0, 0, 0), vec3(1, 1, 1), 1)) {
		
		model = ModelManager::instance()->getModel("car");
		if (model == NULL)
			this->isActive = false;

		
	}
	virtual ~Car() {}
	int getAngle() { return angle; }

	void drawLights();
	virtual void draw();
	void updateLights();
	void update(float timeStep);


	void toogleSpotLights() {
		if (leftLight.isActive || rightLight.isActive) {
			leftLight.isActive = false;
			rightLight.isActive = false;
		}
		else {
			leftLight.isActive = true;
			rightLight.isActive = true;
		}

	}

	void updateHitbox();

};
