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
#include "Track.h"

#include "ShaderManager.h"
#include "ModelManager.h"
#include "ObjLoader.h"
#include "LightShader.h"
#include "AVTmathLib.h"


#define WIDTH 1200
#define HEIGHT 900
#define CAR_LIVES 5
#define PI 3.141592657
#define MES_WIDTH 700.0f
#define MES_HEIGHT 500.0f


class GameManager {
	
	int oldTime = 0;	// miliseconds

	bool pause = false;
	bool gameOver = false;
	int carLives = CAR_LIVES;
	
	Shader* shader;

	//External array storage defined in AVTmathLib.cpp
	GLint pvm_uniformId;
	GLint vm_uniformId;
	GLint normal_uniformId;
	GLint lPos_uniformId;

	// Mouse Tracking Variables
	int startX, startY, tracking = 0;
	int deltaX = 0, deltaY = 0;
	float cameraRotationAngle = 0;
	
	Car* car;
	Track* track;
	Camera* cameras[3];
	Camera* activeCamera;

public:
	GameManager();

	~GameManager();

	bool getPause() { return pause; }

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

	void display();
	void displayHUD();

	void update(double timeStep);
	void reshape(GLsizei w, GLsizei h);
	void reshapeAVT(GLsizei w, GLsizei h);
	void restart();

};