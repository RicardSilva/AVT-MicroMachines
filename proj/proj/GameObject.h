#pragma once
#include "vec3.h"
#include "Shader.h"
#include "Mesh.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "AVTmathLib.h"

class GameObject {

	
	ObjLoader* loader;
	

protected:
	Shader* shader;
	ObjModel* model;

	

	vec3 position;
	vec3 speed;
	int angle;

public:
	bool isActive = true;

	GameObject() {}
	GameObject(vec3& position, vec3& speed, float angle)
		: position(position), speed(speed), angle(angle) {
		shader = ShaderManager::instance()->getShader("lightShader");
	}
	GameObject(vec3& position) : position(position), speed(vec3(0, 0, 0)), angle(0) {
		shader = ShaderManager::instance()->getShader("lightShader");
	}
	virtual ~GameObject() {}

	vec3 getPosition() { return position; }

	virtual void draw();
	virtual void update(float timeStep) = 0;

};