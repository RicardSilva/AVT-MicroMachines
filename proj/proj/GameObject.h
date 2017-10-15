#pragma once
#include "vec3.h"
#include "Shader.h"
#include "Mesh.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "Hitbox.h"
#include "AVTmathLib.h"

#define PI 3.14

class GameObject {

	
	ObjLoader* loader;
	

protected:
	Shader* shader;
	ObjModel* model;

	Hitbox *hitbox;

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
	GameObject(vec3& position, vec3& speed, float angle, Hitbox *hitbox)
		: position(position), speed(speed), angle(angle), hitbox(hitbox) {
		shader = ShaderManager::instance()->getShader("lightShader");
	}
	GameObject(vec3& position, Hitbox *hitbox) : position(position), speed(vec3(0, 0, 0)), angle(0), hitbox(hitbox) {
		shader = ShaderManager::instance()->getShader("lightShader");
	}
	virtual ~GameObject() {}

	vec3 getPosition() { return position; }

	Hitbox *getHitbox() { return hitbox; }

	virtual void draw();
	virtual void update(float timeStep) = 0;

};