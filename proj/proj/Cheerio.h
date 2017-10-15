#pragma once
#include "GameObject.h"

#define CHEERIO_INNER 3
#define CHEERIO_OUTER 6

class Cheerio : public GameObject {

	float inercia = 320;

public:
	Cheerio(vec3& position)  //TODO
		: GameObject(position, new Hitbox(vec3(position.x - CHEERIO_OUTER - (CHEERIO_OUTER - CHEERIO_INNER), position.y - CHEERIO_OUTER - (CHEERIO_OUTER - CHEERIO_INNER), position.z - (CHEERIO_OUTER - CHEERIO_INNER)),
										vec3(position.x + CHEERIO_OUTER + (CHEERIO_OUTER - CHEERIO_INNER), position.y + CHEERIO_OUTER + (CHEERIO_OUTER - CHEERIO_INNER), position.z + CHEERIO_OUTER - CHEERIO_INNER)))
	{
		model = ModelManager::instance()->getModel("cheerio");

		if (model == NULL)
			this->isActive = false;
	}
	virtual ~Cheerio() {}

	void draw();
	void update(float timeStep);

};