#ifndef __HITBOX_H__
#define __HITBOX_H__

#include "AVTmathLib.h"
#include "Shader.h"
#include "Mesh.h"
#include "ShaderManager.h"
#include "ModelManager.h"

#define DEBUG_ACTIVE false

class Hitbox {

	Shader* shader;
	ObjModel* model;
public:
	vec3 minCorner;
	vec3 maxCorner;
	vec3 center;


	Hitbox(vec3 minCorner, vec3 maxCorner) : minCorner(minCorner), maxCorner(maxCorner), 
		center(vec3(minCorner.x + (maxCorner.x - minCorner.x) / 2.0f,
			minCorner.y + (maxCorner.y - minCorner.y) / 2.0f,
			minCorner.z + (maxCorner.z - minCorner.z) / 2.0f)) {
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

	const double getHalfX() const { return (getXmax() - getXmin()) / 2.0; }

	const double getHalfY() const { return (getYmax() - getYmin()) / 2.0; }

	const double getHalfZ() const { return (getZmax() - getZmin()) / 2.0; }

	bool hasCollision(Hitbox *h);

	void set(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax);
	void draw();

};

#endif