#ifndef __HITBOX_H__
#define __HITBOX_H__

#include "AVTmathLib.h"
#include "Shader.h"
#include "Mesh.h"
#include "ShaderManager.h"
#include "ModelManager.h"

#define DEBUG_ACTIVE true

class Hitbox {

	Shader* shader;
	ObjModel* model;

	vec3 minCorner;
	vec3 maxCorner;

public:
	Hitbox(vec3 minCorner, vec3 maxCorner) : minCorner(minCorner), maxCorner(maxCorner) {
		shader = ShaderManager::instance()->getShader("lightShader");
		model = ModelManager::instance()->getModel("cube");
	}

	~Hitbox() {}
	const double getXmin() const { return minCorner.x; }

	const double getXmax() const { return maxCorner.x; }

	const double getYmin() const { return minCorner.y; }

	const double getYmax() const { return maxCorner.y; }

	const double getZmin() const { return minCorner.z; }

	const double getZmax() const { return maxCorner.z; }

	const double getHalfX() const { return (getXmax() - getXmin()) / 2; }

	const double getHalfY() const { return (getYmax() - getYmin()) / 2; }

	const double getHalfZ() const { return (getZmax() - getZmin()) / 2; }

	bool hasCollision(Hitbox *h);

	void set(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);

	vec3 &getCenter() const;

	void draw();

};

#endif