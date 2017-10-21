#include "Hitbox.h"

bool Hitbox::hasCollision(Hitbox *h) {
	bool t = ((getXmax() > h->getXmin()) && (getXmin() < h->getXmax()) && (getZmax() > h->getZmin()) && (getZmin() < h->getZmax()));
	return t;
}

void Hitbox::set(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax) {
	minCorner = vec3(xmin, ymin, zmin);
	maxCorner = vec3(xmax, ymax, zmax);
}

vec3& Hitbox::getCenter() const {
	return vec3(getXmin() + (getXmax() - getXmin()) / 2, getYmin() + (getYmax() - getYmin()) / 2, getZmin() + (getZmax() - getZmin()) / 2);
}