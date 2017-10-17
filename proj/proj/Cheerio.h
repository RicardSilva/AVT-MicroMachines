#pragma once
#include "GameObject.h"

#define CHEERIO_WIDTH 4.5
#define CHEERIO_LENGTH 15
#define CHEERIO_HEIGHT 15

class Cheerio : public GameObject {

	float inercia = 320;

public:
	Cheerio(vec3& position)
		: GameObject(position, new Hitbox(vec3(position.x - CHEERIO_LENGTH / 2.0, position.y - CHEERIO_HEIGHT / 2.0, position.z - CHEERIO_WIDTH / 2.0),
										vec3(position.x + CHEERIO_LENGTH / 2.0, position.y + CHEERIO_HEIGHT / 2.0, position.z + CHEERIO_WIDTH / 2.0)))
	{
		model = ModelManager::instance()->getModel("cheerio");

		if (model == NULL)
			this->isActive = false;
	}
	virtual ~Cheerio() {}

	void draw();
	void update(float timeStep);

	void updateHitbox();
};