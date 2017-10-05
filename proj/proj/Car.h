#pragma once
#include "vec3.h"
#include "AVTmathLib.h"
#include "GameObject.h"

class Car : public GameObject {
	
	vec3 position;
	float angle;
	
	

public:
	Car(vec3& position, Shader* shader) 
		: GameObject(position, shader, std::string("objs/car2.obj")) {
		
	}
	virtual ~Car() {}

	
	void update(float timeStep);


};
