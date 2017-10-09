#pragma once
#include "vec3.h"
#include "GameObject.h"
#include "Cheerio.h"
#include "Orange.h"
#include "Butter.h"
#include "MathHelper.h"
#include "Light.h"
#include "DirectionalLight.h"

#define TRACK_WIDTH 1400
#define TRACK_HEIGHT 1000
#define MAX_ORANGES 3

#define ORANGE_BASE_SPEED 50

class Track : public GameObject {

	std::vector<Cheerio*> cheerios;
	std::vector<Butter*> butters;
	std::vector<Orange*> oranges;
	DirectionalLight dirLight;

	vec3 startingPosition;
	int orangeCounter;

public:
	Track(vec3& position) 
		: GameObject(position), orangeCounter(0) {
		model = ModelManager::instance()->getModel("track");
		importFromFile(std::string("tracks/track.txt"));
		Orange* o;
		for (int i = 0; i < MAX_ORANGES; i++) {
			o = new Orange();
			o->isActive = false;
			oranges.push_back(o);
		}

		dirLight = DirectionalLight(vec3(-1, 1, -1), vec3(0,0,1));
	}
	virtual ~Track() {}
	void setStartingPosition(vec3& position) {
		startingPosition = position;
	}

	void attemptToSpawnOrange();
	
	void update(float timeStep);
	void draw() override;

private:
	void importFromFile(std::string& s);

};