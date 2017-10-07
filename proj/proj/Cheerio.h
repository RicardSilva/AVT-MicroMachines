#pragma once
#include "GameObject.h"
class Cheerio : public GameObject {

public:
	Cheerio(vec3& position) 
		: GameObject(position) {
		model = ModelManager::instance()->getModel("cheerio");
	}
	virtual ~Cheerio() {}

	void draw();
	void update(float timeStep) {}

};