#pragma once
#include "vec3.h"
#include "AVTmathLib.h"
#include "GameObject.h"

class Car : public GameObject {
	
	vec3 position;
	float angle;
	
	

public:
	Car(vec3& position) 
		: GameObject(position) {
		model = ModelManager::instance()->getModel("car");
		
	}
	virtual ~Car() {}


	virtual void draw();
	void update(float timeStep);


};
