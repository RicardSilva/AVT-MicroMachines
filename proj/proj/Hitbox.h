#ifndef __HITBOX_H__
#define __HITBOX_H__

#include "AVTmathLib.h"


class Hitbox {
	vec3 _minCorner;
	vec3 _maxCorner;

public:
	Hitbox(vec3 minCorner, vec3 maxCorner) : _minCorner(minCorner), _maxCorner(maxCorner) {}

	~Hitbox() {}
	const double getXmin() const { return _minCorner.x; }

	const double getXmax() const { return _maxCorner.x; }

	const double getYmin() const { return _minCorner.y; }

	const double getYmax() const { return _maxCorner.y; }

	const double getZmin() const { return _minCorner.z; }

	const double getZmax() const { return _maxCorner.z; }

	const double getHalfX() const { return (getXmax() - getXmin()) / 2; }

	const double getHalfY() const { return (getYmax() - getYmin()) / 2; }

	const double getHalfZ() const { return (getZmax() - getZmin()) / 2; }

	bool hasCollision(Hitbox *h);

	void set(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);

	vec3 &getCenter() const;

	//void draw();
};

#endif