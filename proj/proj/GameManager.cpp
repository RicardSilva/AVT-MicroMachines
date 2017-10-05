#include "GameManager.h"
bool isOpenGLError() {
	bool isError = false;
	GLenum errCode;
	const GLubyte *errString;
	while ((errCode = glGetError()) != GL_NO_ERROR) {
		isError = true;
		errString = gluErrorString(errCode);
		std::cerr << "OpenGL ERROR [" << errString << "]." << std::endl;
	}
	return isError;
}
void checkOpenGLError(std::string error)
{
	if (isOpenGLError()) {
		std::cerr << error << std::endl;
		getchar();
		exit(EXIT_FAILURE);
	}
}
GameManager::GameManager() { }

GameManager::~GameManager() { }

void GameManager::onTimer(int value) {
	if (!pause && !gameOver) {
		int time = glutGet(GLUT_ELAPSED_TIME);
		int timeStep = time - oldTime;
		oldTime = time;
		update(timeStep);
	}
	else {
		oldTime = glutGet(GLUT_ELAPSED_TIME);
	}
	glutPostRedisplay();
}


void GameManager::init() {

	srand(time(NULL));	// initialize seed of random

	initShaders();
	car = new Car(vec3(0,0,0), shader);
	initCameras();
	initLights();
	initTrack();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);


}

void GameManager::initShaders() {
	shader = new LightShader("shaders/pointlight.vert", "shaders/pointlight.frag");
}

void GameManager::initCameras() {
	// set the camera position based on its spherical coordinates

	Camera* topCamera = new OrthoCamera(-800,800,-800,800, 0.1,100);
	topCamera->setEye(vec3(0,20,0));
	topCamera->setTarget(vec3(0,0,0));
	topCamera->setUp(vec3(0,0,-1));

	cameras[0] = topCamera;

	Camera* topPerspCamera = new PerspectiveCamera(50, (float)WIDTH / HEIGHT, 0.1f, 10.0f);
	topPerspCamera->setEye(vec3(5, 5, -5));
	topPerspCamera->setTarget(vec3(0, 0, 0));
	topPerspCamera->setUp(vec3(0, 1, 0));

	cameras[1] = topPerspCamera;

	Camera* carCamera = new PerspectiveCamera(50, (float)WIDTH / HEIGHT, 0.1f, 10.0f);
	carCamera->setEye(vec3(5, 5, -5));
	carCamera->setTarget(vec3(0, 0, 0));
	carCamera->setUp(vec3(0, 1, 0));

	cameras[2] = carCamera;

	activeCamera = cameras[0];

}

void GameManager::initLights() {
	
}

void GameManager::initTrack() {
	track = new Track(vec3(0,0,0), shader);
}


void GameManager::idle() {
	// do nothing
}

void GameManager::keydown(int key) {
	// key = pressed key
	key = tolower(key);
	switch (key) {
	case 27:
		glutLeaveMainLoop();
		break;
	case '1':
		activeCamera = cameras[0];
		break;
	case '2':
		activeCamera = cameras[1];
		break;
	case '3':
		activeCamera = cameras[2];
		break;
	}

}

void GameManager::specialKeydown(int key) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		//_car->setRight(1);
		break;
	case GLUT_KEY_LEFT:
		//_car->setLeft(1);
		break;
	case GLUT_KEY_UP:
		//_car->setThrottle(1);
		break;
	case GLUT_KEY_DOWN:
		//_car->setThrottle(-1);
		break;
	}
}

void GameManager::specialKeyup(int key) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		//_car->setRight(0);
		break;
	case GLUT_KEY_LEFT:
		//_car->setLeft(0);
		break;
	case GLUT_KEY_UP:
		//_car->setThrottle(0);
		break;
	case GLUT_KEY_DOWN:
		//_car->setThrottle(0);
		break;
	}
}

void GameManager::display() {
	//GLint loc;

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// load identity matrices
	
	loadIdentity(MODEL);
	// set the camera using a function similar to gluLookAt
	
	activeCamera->computeView();
	activeCamera->computeProjection(WIDTH, HEIGHT);
	shader->use();

	//send the light position in eye coordinates
	float lightPos[4] = { 0.0f, 5.0f, 0.0f, 1.0f };
	float res[4];
	multMatrixPoint(VIEW, lightPos, res);   //lightPos definido em World Coord so is converted to eye space
	glUniform4fv(lPos_uniformId, 1, res);
	shader->unUse();
	// Render objects
	car->draw();
	track->draw();
	


	glutSwapBuffers();
	displayHUD();
}

void GameManager::displayHUD() {
	


}

void GameManager::teste(GLfloat *value) {
	glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, value);
}
void GameManager::update(double timeStep) {


	
}

void GameManager::restart() {
	
}

void GameManager::reshape(GLsizei w, GLsizei h) {
	// When viewport is resized, objects scale with it
	float ratio = (float)WIDTH / HEIGHT;
	float aspect = (float)w / h;

	// adapt viewport
	if (ratio < aspect)
		glViewport((w - h*ratio) / 2.0f, 0, h*ratio, h);
	else
		glViewport(0, (h - w / ratio) / 2, w, w / ratio);
}
void GameManager::reshapeAVT(GLsizei w, GLsizei h) {
	float ratio;
	// Prevent a divide by zero, when window is too short
	if (h == 0)
		h = 1;
	// set the viewport to be the entire window
	glViewport(0, 0, w, h);
	// set the projection matrix
	ratio = (1.0f * w) / h;
	loadIdentity(PROJECTION);
	perspective(53.13f, ratio, 0.1f, 1000.0f);
}