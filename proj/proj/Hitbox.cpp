#include "Hitbox.h"

bool Hitbox::hasCollision(Hitbox *h) {
	bool t = ((getXmax() > h->getXmin()) && (getXmin() < h->getXmax()) && (getYmax() > h->getYmin()) && (getYmin() < h->getYmax()));
	return t;
}

void Hitbox::set(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax) {
	_minCorner = vec3(xmin, ymin, zmin);
	_maxCorner = vec3(xmax, ymax, zmax);
}

vec3 &Hitbox::getCenter() const {
	return *new vec3(getXmin() + (getXmax() - getXmin()) / 2, getYmin() + (getYmax() - getYmin()) / 2, getZmin() + (getZmax() - getZmin()) / 2);
}

//void Hitbox::draw() {
//	glPushMatrix();
//	glColor3f(0.0, 0.0, 1.0);
//	glTranslatef((getXmax() - (getXmax() - getXmin()) / 2),
//		getYmax() - (getYmax() - getYmin()) / 2,
//		getZmax() - (getZmax() - getZmin()) / 2);
//	glScalef(getXmax() - getXmin(), getYmax() - getYmin(), getZmax() - getZmin());
//
//
//	glutWireCube(1);
//
//	glPopMatrix();
//}