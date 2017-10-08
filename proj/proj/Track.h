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
	Track(vec3& position) 
		: GameObject(position) {
		model = ModelManager::instance()->getModel("track");
		importFromFile(std::string("tracks/track.txt"));
		this->oranges.push_back(new Orange(vec3(0,50, 0)));
	}
	virtual ~Track() {}
	void setStartingPosition(vec3& position) {
		startingPosition = position;
	}
	void importFromFile(std::string& s);
	void update(float timeStep);
	void draw() override;

};