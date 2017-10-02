#include <math.h>
#include <iostream>
#include <sstream>

#include <string>
#include "GameManager.h"

#include <GL/glew.h>
#include <GL/freeglut.h>




#define CAPTION "MicroMachines"
int WindowHandle = 0;
int WinX = 640, WinY = 480;

GameManager* gm;

// Frame counting and FPS computation
unsigned int FrameCount = 0;
long myTime, timebase = 0, frame = 0;
char s[32];

void FPScounter(int value)
{
	std::ostringstream oss;
	oss << CAPTION << ": " << FrameCount << " FPS @ (" << WinX << "x" << WinY << ")";
	std::string s = oss.str();
	glutSetWindow(WindowHandle);
	glutSetWindowTitle(s.c_str());
	FrameCount = 0;
	glutTimerFunc(1000, FPScounter, 0);
}

void refresh(int value)
{
	gm->onTimer(value);
	glutTimerFunc(1000 / 60, refresh, 0);
}



void reshape(int w, int h) {

	gm->reshapeAVT(w, h);
}

void display(void) {
	FrameCount++;
	gm->display();
	
}



void processKeys(unsigned char key, int xx, int yy)
{
	gm->keydown(key);
}

void processMouseButtons(int button, int state, int xx, int yy)
{
	
}
void processMouseMotion(int xx, int yy)
{
}
void mouseWheel(int wheel, int direction, int x, int y) {

	
}



int main(int argc, char **argv) {

	//  GLUT initialization
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);

	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE | GLUT_DEBUG);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(WinX, WinY);
	WindowHandle = glutCreateWindow(CAPTION);


	//  Callback Registration
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutIdleFunc(renderScene);

	//	Mouse and Keyboard Callbacks
	glutKeyboardFunc(processKeys);
	glutMouseFunc(processMouseButtons);
	glutMotionFunc(processMouseMotion);
	glutMouseWheelFunc(mouseWheel);
	glutTimerFunc(0, FPScounter, 0);
	glutTimerFunc(0, refresh, 0);


	//	return from main loop
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//	Init GLEW
	glewExperimental = GL_TRUE;
	glewInit();

	printf("Vendor: %s\n", glGetString(GL_VENDOR));
	printf("Renderer: %s\n", glGetString(GL_RENDERER));
	printf("Version: %s\n", glGetString(GL_VERSION));
	printf("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	gm = new GameManager();
	if (!gm->init())
		return(1);


	//  GLUT main loop
	glutMainLoop();

	return(0);

}

