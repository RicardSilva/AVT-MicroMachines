#pragma once
#include "vec3.h"
#include "GameObject.h"
#include "Cheerio.h"
#include "Orange.h"
#include "Butter.h"

class Track : public GameObject {

	std::vector<Cheerio*> cheerios;
	std::vector<Butter*> butters;
	std::vector<Orange*> oranges;

	vec3 startingPosition;


public:
	Track(vec3& position, Shader* shader) 
		: GameObject(position, shader, std::string("objs/cube.obj")) {
		importFromFile(std::string("tracks/track.txt"));
		int i = 2;
	}
	virtual ~Track() {}
	void setStartingPosition(vec3& position) {
		startingPosition = position;
	}
	void importFromFile(std::string& s);
	void update(float timeStep);
	void draw() override;

};