#pragma once
#include "GameObject.h"
class Cheerio : public GameObject {

public:
	Cheerio(vec3& position, Shader* shader) 
		: GameObject(position, shader, std::string("objs/donut1.obj")) {
	}
	virtual ~Cheerio() {}

	void update(float timeStep) {}

};