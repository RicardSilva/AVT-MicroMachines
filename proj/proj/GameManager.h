#pragma once

#include <stdlib.h>
#include <ctype.h>
#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>
#include <array>
#include "Car.h"
#include "Track.h"
#include "OrthoCamera.h"
#include "PerspectiveCamera.h"
#include "time.h"

// Use Very Simple Libs
#include "VSShaderlib.h"
#include "AVTmathLib.h"




#define WIDTH 640
#define HEIGHT 480
#define CAR_LIVES 5
#define PI 3.141592657
#define MES_WIDTH 700.0f
#define MES_HEIGHT 500.0f

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2

// The storage for matrices
extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

// The normal matrix
extern float mNormal3x3[9];


class GameManager {
	
	int oldTime = 0;	// miliseconds

	bool pause = false;
	bool gameOver = false;
	int carLives = CAR_LIVES;
	

	VSShaderLib shader;

	//External array storage defined in AVTmathLib.cpp
	GLint pvm_uniformId;
	GLint vm_uniformId;
	GLint normal_uniformId;
	GLint lPos_uniformId;

	// Camera Position
	float camX, camY, camZ;

	Car* car;
	Track* track;
	Camera* cameras[3];
	Camera* activeCamera;

public:
	GameManager();

	~GameManager();

	bool getPause() { return pause; }

	void onTimer(int value);

	bool init();
	bool initShaders();
	void initCameras();
	void initLights();
	void initTrack();


	void idle();

	void keydown(int key);
	void specialKeydown(int key);
	void specialKeyup(int key);


	void display();
	void displayHUD();

	void drawCar();
	void drawTrack();
	void sendMatricesToShader();
	void teste(GLfloat *value);
	void update(double timeStep);
	void reshape(GLsizei w, GLsizei h);
	void reshapeAVT(GLsizei w, GLsizei h);
	void restart();

};