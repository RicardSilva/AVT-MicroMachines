#pragma once
#include "vec3.h"
#include "GameObject.h"
#include "Cheerio.h"
#include "Orange.h"
#include "Butter.h"
#include "MathHelper.h"
#include "Lamp.h"
#include "Border.h"
#include "DirectionalLight.h"

#include "TGA.h"

#define TRACK_WIDTH 1400
#define TRACK_HEIGHT 1000
#define HALF_TRACK_WIDTH 700
#define HALF_TRACK_HEIGHT 500
#define MAX_ORANGES 3

#define ORANGE_BASE_SPEED 50

class Track : public GameObject {

	GLuint TextureArray[5];

	std::vector<Cheerio*> cheerios;
	std::vector<Butter*> butters;
	std::vector<Orange*> oranges;
	DirectionalLight dirLight;
	std::vector<Lamp*> lamps;
	std::vector<Border*> borders;

	vec3 startingPosition;
	int orangeCounter;

public:
	Track(vec3& position) 
		: GameObject(position), orangeCounter(0),
		dirLight(DirectionalLight(vec4(1, -1, 1, 0), vec3(1, 1, 1), 0.5f)) {

		model = ModelManager::instance()->getModel("track");

		if (model == NULL)
			this->isActive = false;

		glGenTextures(5, TextureArray);
		TGA_Texture(TextureArray, "textures/wood_diffuse.tga", 0);
		TGA_Texture(TextureArray, "textures/wood_specular.tga", 1);
		TGA_Texture(TextureArray, "textures/bamboo_diffuse.tga", 2);
		TGA_Texture(TextureArray, "textures/bamboo_specular.tga", 3);
		TGA_Texture(TextureArray, "textures/mask.tga", 4);

		loadFromFile(std::string("tracks/track.txt"));

	/*	Orange* o;
		for (int i = 0; i < MAX_ORANGES; i++) {
			o = new Orange();
			o->isActive = false;
			oranges.push_back(o);
		}*/


		borders.push_back(new Border(vec3(TRACK_WIDTH + 10, 0, 0), 20.0, TRACK_HEIGHT + 50));
		borders.push_back(new Border(vec3(-TRACK_WIDTH - 10, 0, 0), 20.0, TRACK_HEIGHT + 50));
		borders.push_back(new Border(vec3(0, 0, TRACK_HEIGHT + 10), TRACK_WIDTH + 50, 20.0));
		borders.push_back(new Border(vec3(0, 0, -TRACK_HEIGHT - 10), TRACK_WIDTH + 50, 20.0));

	}
	virtual ~Track() {}

	vec3 getStartingPosition() {
		return startingPosition;
	}

	std::vector<Cheerio*> getCheerios() {
		return cheerios;
	}

	std::vector<Butter*> getButters() {
		return butters;
	}

	std::vector<Orange*> getOranges() {
		return oranges;
	}

	std::vector<Lamp*> getLamps() {
		return lamps;
	}

	std::vector<Border*> getBorders() {
		return borders;
	}

	void attemptToSpawnOrange();
	void increaseOrangeSpeed();
	
	void update(float timeStep);
	void drawLights();
	void draw() override;

	void toogleDirectionalLight() {
		if (dirLight.isActive) {
			dirLight.isActive = false;
			glClearColor(0.1, 0.1, 0.1, 1);
		}
		else {
			dirLight.isActive = true;
			glClearColor(0.53, 0.81, 0.92, 1);
		}

	}
	void tooglePointLights() {
		for (auto lamp : lamps)
			lamp->toogleLight();
	}

	void updateHitbox() {};

private:
	void loadFromFile(std::string& s);

};