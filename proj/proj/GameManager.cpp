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

void GameManager::onRefreshTimer(int value) {
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
void GameManager::onSpawnOrangeTimer() {
	track->attemptToSpawnOrange();
}


void GameManager::init() {

	srand(time(NULL));	// initialize seed of random

	initShaders();
	initMeshes();
	car = new Car(vec3(0,0,0));
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
	ShaderManager::instance()->addShader("lightShader", shader);
}
void GameManager::initMeshes() {
	ObjLoader* loader = new ObjLoader();
	ObjModel* model;
		
	std::vector<pair<string, string>> modelsToLoad;
	modelsToLoad.push_back(std::make_pair("car", "objs/car.obj"));
	modelsToLoad.push_back(std::make_pair("track", "objs/table.obj"));
	modelsToLoad.push_back(std::make_pair("cheerio", "objs/donut.obj"));
	modelsToLoad.push_back(std::make_pair("butter", "objs/butter.obj"));
	modelsToLoad.push_back(std::make_pair("orange", "objs/Orange.obj"));

	for (auto m : modelsToLoad) {
		if (loader->LoadFile(m.second)) {
			model = loader->LoadedModel;
			ModelManager::instance()->addModel(m.first, model);
		}
		else
			std::cerr << m.second << ": invalid .obj file" << std::endl;
	}
	
}
void GameManager::initCameras() {
	// set the camera position based on its spherical coordinates

	Camera* topCamera = new OrthoCamera(-750, 750,-550,550, 0.1,150);
	topCamera->setEye(vec3(0,100,0));
	topCamera->setTarget(vec3(0,0,0));
	topCamera->setUp(vec3(0,0,-1));

	cameras[0] = topCamera;

	Camera* topPerspCamera = new PerspectiveCamera(70, (float)WIDTH / HEIGHT, 0.1f, 1500.0f);
	topPerspCamera->setEye(vec3(0, 600, 900));
	topPerspCamera->setTarget(vec3(0, 0, 150));
	topPerspCamera->setUp(vec3(0, 0, -1));

	cameras[1] = topPerspCamera;

	Camera* carCamera = new PerspectiveCamera(60, (float)WIDTH / HEIGHT, 0.1f, 1000.0f);
	carCamera->setEye(vec3(0, 50, -80));
	carCamera->setTarget(vec3(0, 0, 0));
	carCamera->setUp(vec3(0, 1, 0));

	cameras[2] = carCamera;

	activeCamera = cameras[0];

}
void GameManager::initLights() {
	
}
void GameManager::initTrack() {
	track = new Track(vec3(0,-0.1,0));
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
	case 'd':
		car->turnRight = true;
		break;
	case 's':
		car->goBack = true;
		break;
	case 'w':
		car->goForward = true;
		break;
	case 'a':
		car->turnLeft = true;
		break;
	}

}

void GameManager::keyup(int key) {
	// key = pressed key
	key = tolower(key);
	switch (key) {
	case 'd':
		car->turnRight = false;
		break;
	case 's':
		car->goBack = false;
		break;
	case 'w':
		car->goForward = false;
		break;
	case 'a':
		car->turnLeft = false;
		break;
	}

}

void GameManager::specialKeydown(int key) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		car->turnRight = true;
		break;
	case GLUT_KEY_LEFT:
		car->turnLeft = true;
		break;
	case GLUT_KEY_UP:
		car->goForward = true;
		break;
	case GLUT_KEY_DOWN:
		car->goBack = true;
		break;
	}
}

void GameManager::specialKeyup(int key) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		car->turnRight = false;
		break;
	case GLUT_KEY_LEFT:
		car->turnLeft = false;
		break;
	case GLUT_KEY_UP:
		car->goForward = false;
		break;
	case GLUT_KEY_DOWN:
		car->goBack = false;
		break;
	}
}

void GameManager::mouseButtons(int button, int state, int xx, int yy)
{
	// start tracking the mouse
	if (state == GLUT_DOWN) {
		startX = xx;
		startY = yy;
		deltaX = startX;
		if (button == GLUT_LEFT_BUTTON)
			tracking = 1;
		else if (button == GLUT_RIGHT_BUTTON)
			tracking = 2;
	}

	//stop tracking the mouse
	else if (state == GLUT_UP) {
		tracking = 0;
	}
}

// Track mouse motion while buttons are pressed

void GameManager::mouseMotion(int xx, int yy) {
	
	// left mouse button: move camera
	if (tracking == 1) {
		if (deltaX > xx) {
			cameraRotationAngle += 1.0f;
		}
		else if (deltaX < xx) {
			cameraRotationAngle -= 1.0f;
		}
		deltaX = xx;

	}
}

void GameManager::mouseWheel(int wheel, int direction, int x, int y) {
	//
	//	r += direction * 0.1f;
	//	if (r < 0.1f)
	//		r = 0.1f;
	//
	//	camX = r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	//	camZ = r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
	//	camY = r *   						     sin(beta * 3.14f / 180.0f);
	//
	//	//  uncomment this if not using an idle func
	//	//	glutPostRedisplay();
}

void GameManager::display() {	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	loadIdentity(MODEL);	
	activeCamera->computeView();
	//car camera rotation
	if (cameraRotationAngle != 0 && activeCamera == cameras[2]) {
		//rotate around car
		translate(VIEW, car->getPosition());
		rotate(VIEW, cameraRotationAngle, vec3(0, 1, 0));
		translate(VIEW, -(car->getPosition()));
		
		if (tracking == 0) { //mouse released -> return to original rotation
			if (cameraRotationAngle > 0)
				cameraRotationAngle = max(cameraRotationAngle - 2.5f, 0.0f);
			else
				cameraRotationAngle = min(cameraRotationAngle + 2.5f, 0.0f);
		}
	}
	activeCamera->computeProjection(WIDTH, HEIGHT);

	// Render objects
	track->drawLights();
	car->drawLights();

	track->draw(); 
	car->draw();
	
	


	glutSwapBuffers();
	displayHUD();
}

void GameManager::displayHUD() {
	


}
void GameManager::update(double timeStep) {

	car->update(timeStep);
	track->update(timeStep);
	cameras[2]->computeCarCameraPosition(car->getPosition(), car->getAngle());
	
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