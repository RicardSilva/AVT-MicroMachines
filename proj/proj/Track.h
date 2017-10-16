#pragma once
#include "vec3.h"
#include "GameObject.h"
#include "Cheerio.h"
#include "Orange.h"
#include "Butter.h"
#include "MathHelper.h"
#include "Lamp.h"
#include "DirectionalLight.h"

#define TRACK_WIDTH 1400
#define TRACK_HEIGHT 1000
#define HALF_TRACK_WIDTH 700
#define HALF_TRACK_HEIGHT 500
#define MAX_ORANGES 3

#define ORANGE_BASE_SPEED 50

class Track : public GameObject {

	std::vector<Cheerio*> cheerios;
	std::vector<Butter*> butters;
	std::vector<Orange*> oranges;
	DirectionalLight dirLight;
	std::vector<Lamp*> lamps;

	vec3 startingPosition;
	int orangeCounter;

public:
	Track(vec3& position) 
		: GameObject(position), orangeCounter(0) {
		model = ModelManager::instance()->getModel("track");

		if (model == NULL)
			this->isActive = false;
		loadFromFile(std::string("tracks/track.txt"));
		Orange* o;
		for (int i = 0; i < MAX_ORANGES; i++) {
			o = new Orange();
			o->isActive = false;
			oranges.push_back(o);
		}

		dirLight = DirectionalLight(vec4(1, -1, 1, 0), vec3(1,1,1), 0.5f);
	}
	virtual ~Track() {}
	void setStartingPosition(vec3& position) {
		startingPosition = position;
	}

	void attemptToSpawnOrange();
	
	void update(float timeStep);
	void drawLights();
	void draw() override;

	void toogleDirectionalLight() {
		if (dirLight.isActive) {
			dirLight.isActive = false;
			shader->decActiveLights();
			glClearColor(0.1, 0.1, 0.1, 1);
		}
		else {
			dirLight.isActive = true;
			shader->incActiveLights();
			glClearColor(0.53, 0.81, 0.92, 1);
		}

	}
	void tooglePointLights() {
		for (auto lamp : lamps)
			lamp->toogleLight();
	}

private:
	void loadFromFile(std::string& s);

};