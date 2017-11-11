#pragma once

#include <stdlib.h>
#include <ctype.h>
#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>
#include <array>
#include "time.h"

#include "OrthoCamera.h"
#include "PerspectiveCamera.h"

#include "Car.h"
#include "MiniCar.h"
#include "Track.h"
#include "Fog.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "ObjLoader.h"
#include "LightShader.h"
#include "TextureShader.h"
#include "AVTmathLib.h"
#include "TextureHolder.h"
#include "ParticleSystem.h"
#include "LensFlare.h"
#include "Sun.h"


#define WIDTH 1200
#define HEIGHT 900
#define CAR_LIVES 5
#define PI 3.141592657
#define MES_WIDTH 700.0f
#define MES_HEIGHT 500.0f
#define CAPTION "MicroMachines"

class GameManager {

	int oldTime = 0;	// miliseconds

	//GAME LOGIC
	bool pause = false;
	bool gameOver = false;
	int carLives = CAR_LIVES;
	int currentLapTime = 0;
	int bestLapTime = INT_MAX;
	bool startClock = false;
	bool raining = false;
	bool foggy = false;
	bool lensFlaring = false;
	bool day = true;

	// Mouse Tracking Variables
	int startX, startY, tracking = 0;
	int deltaX = 0, deltaY = 0;
	float cameraRotationAngle = 0;

	// Frame counting and FPS computation
	unsigned int FrameCount = 0;
	char s[32];

	Shader* shader;
	Shader* textureShader;
	MiniCar* carLive;
	Car* car;
	Track* track;
	ParticleSystem* rain;
	LensFlare* flare;
	Sun* sun;
	Camera* cameras[5];
	Camera* activeCamera;
	TextureHolder* pauseTexture;
	TextureHolder* gameOverTexture;
	Fog* fog;

public:
	GameManager() {}

	~GameManager() {
		delete(track);
		delete(car);
		delete(cameras[0]);
		delete(cameras[1]);
		delete(cameras[2]);
		delete(cameras[3]);
		delete(pauseTexture);
		delete(gameOverTexture);
		delete(rain); 
		delete(flare);
		delete(sun);
	}

	bool getPause() { return pause; }

	void onFPSCounter(int windowHandle);
	void onRefreshTimer(int value);
	void onSpawnOrangeTimer();
	void onIncreaseOrangeSpeedTimer();

	void init();
	void initShaders();
	void initMeshes();
	void initCameras();
	void initLights();
	void initGameObjects();


	void idle();

	void keydown(int key);
	void keyup(int key);
	void specialKeydown(int key);
	void specialKeyup(int key);

	void mouseButtons(int button, int state, int xx, int yy);
	void mouseMotion(int xx, int yy);
	void mouseWheel(int wheel, int direction, int x, int y);

	bool objectsCollide(GameObject* o1, GameObject* o2);
	void processCarCollisions();
	void processObsCollisions();
	void processCarObstacleCollision(GameObject* obstacle);
	void computePositionAfterCollision(GameObject* obj, GameObject* obstacle);
	void resetCar();
	void restart();

	void display();
	void displayHUD();
	void displayMirrorReflection();
	void displayFlare();

	void update(double timeStep);
	void reshape(GLsizei w, GLsizei h);
	void reshapeAVT(GLsizei w, GLsizei h);

};