#pragma once
#include "GameObject.h"
class Cheerio : public GameObject {

public:
	Cheerio(vec3& position) 
		: GameObject(position) {
		model = ModelManager::instance()->getModel("cheerio");

		if (model == NULL)
			this->isActive = false;
	}
	virtual ~Cheerio() {}

	void draw();
	void update(float timeStep) {}

};