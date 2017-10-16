#pragma once
#include "vec3.h"
#include "AVTmathLib.h"
#include "GameObject.h"
#include "SpotLight.h"
#include "MathHelper.h"

#define PI 3.14

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

	SpotLight lights[2];
	
	

public:
	Car(vec3& position) 
		: GameObject(position) {
		model = ModelManager::instance()->getModel("car");
		if (model == NULL)
			this->isActive = false;

		lights[0] = SpotLight(vec4(position + vec3(14.4, 20, -4.60), 1), vec4(1,0,0,0), vec3(1,1,1), 1);
		lights[1] = SpotLight(vec4(position + vec3(14.4, 20, 4.60), 1), vec4(1, 0, 0, 0), vec3(1, 1, 1), 1);
		//lights[0] = PointLight(vec4(position + vec3(14.4, 4.75, -4.60), 1), vec3(0, 0.0, 1.0), 3);
		//lights[0] = PointLight(vec4(position + vec3(14.4, 4.75, 4.60), 1), vec3(0, 0.0, 1.0), 3);

		
	}
	virtual ~Car() {}
	int getAngle() { return angle; }

	void drawLights();
	virtual void draw();
	void updateLights();
	void update(float timeStep);

	void toogleSpotLights() {
		if (lights[0].isActive || lights[1].isActive) {
			lights[0].isActive = false;
			lights[1].isActive = false;
			shader->decActiveLights();
			shader->decActiveLights();
		}
		else {
			lights[0].isActive = true;
			lights[1].isActive = true;
			shader->incActiveLights();
			shader->incActiveLights();
		}

	}


};
