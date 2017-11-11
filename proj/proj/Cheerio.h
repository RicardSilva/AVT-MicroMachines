#pragma once
#include "GameObject.h"

#define CHEERIO_WIDTH 15
#define CHEERIO_LENGTH 15
#define CHEERIO_HEIGHT 4.5

class Cheerio : public GameObject {

	float inercia = 320;

public:
	Cheerio(vec3& position)
		: GameObject(position, "cheerio", new Hitbox(vec3(position.x - CHEERIO_WIDTH / 2.0, position.y - CHEERIO_HEIGHT / 2.0, position.z - CHEERIO_LENGTH / 2.0),
										vec3(position.x + CHEERIO_WIDTH / 2.0, position.y + CHEERIO_HEIGHT / 2.0, position.z + CHEERIO_LENGTH / 2.0)))
	{ }
	virtual ~Cheerio() {}

	void draw();
	void update(float timeStep);

	void updateHitbox();
};