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
#include "FinishLine.h"
#include "Billboard.h"

#include "TGA.h"

#define TRACK_WIDTH 1400
#define TRACK_HEIGHT 1000
#define HALF_TRACK_WIDTH 700
#define HALF_TRACK_HEIGHT 500
#define MAX_ORANGES 3
#define TRACK_FILE "tracks/track.txt"

#define ORANGE_BASE_SPEED 50

class Track : public GameObject {

	GLuint TextureArray[5];

	std::vector<Cheerio*> cheerios;
	std::vector<Butter*> butters;
	std::vector<Orange*> oranges;
	DirectionalLight dirLight;
	std::vector<Lamp*> lamps;
	std::vector<Border*> borders;
	FinishLine* finishLine;
	Billboard* billboard;
	vec3 startingPosition;
	int orangeCounter;
	float orangeStartingSpeed = 125;

public:
	Track(vec3& position) 
		: GameObject(position), orangeCounter(0),
		dirLight(DirectionalLight(vec4(-1, -1, 0, 0), vec3(1, 1, 1), 0.5f)) {

		model = ModelManager::instance()->getModel("track");

		if (model == NULL)
			this->isActive = false;

		glGenTextures(5, TextureArray);
		TGA_Texture(TextureArray, "textures/wood_diffuse.tga", 0);
		TGA_Texture(TextureArray, "textures/wood_specular.tga", 1);
		TGA_Texture(TextureArray, "textures/bamboo_diffuse.tga", 2);
		TGA_Texture(TextureArray, "textures/bamboo_specular.tga", 3);
		TGA_Texture(TextureArray, "textures/mask.tga", 4);

		loadFromFile(std::string(TRACK_FILE));

		billboard = new Billboard(vec3(0, -10, 0), "textures/christmastree.tga", "lightShader", "billboard");

		borders.push_back(new Border(vec3(HALF_TRACK_WIDTH + 50, 0, 0), 20.0, TRACK_HEIGHT + 50));
		borders.push_back(new Border(vec3(-HALF_TRACK_WIDTH - 50, 0, 0), 20.0, TRACK_HEIGHT + 50));
		borders.push_back(new Border(vec3(0, 0, HALF_TRACK_HEIGHT + 50), TRACK_WIDTH + 50, 20.0));
		borders.push_back(new Border(vec3(0, 0, -HALF_TRACK_HEIGHT - 50), TRACK_WIDTH + 50, 20.0));

		finishLine = new FinishLine(startingPosition + vec3(45, 0,15), 20.0, 50.0);

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

	FinishLine* getFinishLine() {
		return finishLine;
	}

	void attemptToSpawnOrange();
	void increaseOrangeSpeed();
	
	void update(float timeStep);
	void drawLights();
	void draw(vec3 cam);

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
	void restart();
private:
	void loadFromFile(std::string& s);

};