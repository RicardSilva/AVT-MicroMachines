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

public:
	GameObject(vec3& position) : position(position) {
		shader = ShaderManager::instance()->getShader("lightShader");
	}
	virtual ~GameObject() {}

	vec3 getPosition() { return position; }

	virtual void draw();
	virtual void update(float timeStep) = 0;

};