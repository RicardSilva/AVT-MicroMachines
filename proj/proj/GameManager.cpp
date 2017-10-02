#include "GameManager.h"

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


bool GameManager::init() {

	srand(time(NULL));	// initialize seed of random
	if (!initShaders())
		return(false);

	car = new Car();
	initCameras();
	initLights();
	initTrack();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_MULTISAMPLE);
	glClearColor(0.1f, 0.1f, 0.1f, 0.1f);

	return true;

}

bool GameManager::initShaders() {
	// Shader for models
	shader.init();
	shader.loadShader(VSShaderLib::VERTEX_SHADER, "shaders/pointlight.vert");
	shader.loadShader(VSShaderLib::FRAGMENT_SHADER, "shaders/pointlight.frag");

	// set semantics for the shader variables
	glBindFragDataLocation(shader.getProgramIndex(), 0, "colorOut");
	glBindAttribLocation(shader.getProgramIndex(), VERTICES, "position");
	glBindAttribLocation(shader.getProgramIndex(), NORMALS, "normal");
	glBindAttribLocation(shader.getProgramIndex(), TEXCOORDS, "texCoord");

	glLinkProgram(shader.getProgramIndex());

	pvm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_pvm");
	vm_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_viewModel");
	normal_uniformId = glGetUniformLocation(shader.getProgramIndex(), "m_normal");
	lPos_uniformId = glGetUniformLocation(shader.getProgramIndex(), "l_pos");

	printf("InfoLog for Hello World Shader\n%s\n\n", shader.getAllInfoLogs().c_str());

	return(shader.isProgramValid());
}

void GameManager::initCameras() {
	// set the camera position based on its spherical coordinates

	Camera* topCamera = new OrthoCamera(-5,5,-5,5,0.1,10);
	topCamera->setEye(vec3(5,5,-5));
	topCamera->setTarget(vec3(0,0,0));
	topCamera->setUp(vec3(0,1,0));

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
	track = new Track();
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
	GLint loc;

	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// load identity matrices
	
	loadIdentity(MODEL);
	// set the camera using a function similar to gluLookAt
	
	activeCamera->computeView();
	activeCamera->computeProjection(WIDTH, HEIGHT);
	// use our shader
	glUseProgram(shader.getProgramIndex());

	//send the light position in eye coordinates

	//glUniform4fv(lPos_uniformId, 1, lightPos); //efeito capacete do mineiro, ou seja lighPos foi definido em eye coord 

	//float res[4];
	//multMatrixPoint(VIEW, lightPos, res);   //lightPos definido em World Coord so is converted to eye space
	//glUniform4fv(lPos_uniformId, 1, res);



	// send matrices to OGL
	/*computeDerivedMatrix(PROJ_VIEW_MODEL);
	glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
	glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
	computeNormalMatrix3x3();
	glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);*/

	// Render objects
	drawCar();
	drawTrack();
	
	


	glutSwapBuffers();
	displayHUD();
}

void GameManager::displayHUD() {
	


}

void GameManager::drawCar() {
	pushMatrix(MODEL);
	loadIdentity(MODEL);
	translate(MODEL, car->getPosition());

	// send matrices to OGL
	computeDerivedMatrix(PROJ_VIEW_MODEL);
	glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
	glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
	computeNormalMatrix3x3();
	glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);

	car->draw();
	popMatrix(MODEL);

}

void GameManager::drawTrack() {
	pushMatrix(MODEL);
	loadIdentity(MODEL);
	scale(MODEL, 50,0.5f,50);
	translate(MODEL, 0, 0, 0);

	// send matrices to OGL
	computeDerivedMatrix(PROJ_VIEW_MODEL);
	glUniformMatrix4fv(vm_uniformId, 1, GL_FALSE, mCompMatrix[VIEW_MODEL]);
	glUniformMatrix4fv(pvm_uniformId, 1, GL_FALSE, mCompMatrix[PROJ_VIEW_MODEL]);
	computeNormalMatrix3x3();
	glUniformMatrix3fv(normal_uniformId, 1, GL_FALSE, mNormal3x3);

	track->draw();
	popMatrix(MODEL);
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
		glViewport((w - h*ratio) / 2, 0, h*ratio, h);
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