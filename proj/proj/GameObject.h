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
	Hitbox *hitbox;
	vec3 speed;
	int angle;

public:
	bool isActive = true;
	vec3 position;
	ObjModel* model;

	GameObject() {}

	GameObject(vec3& position) : position(position), speed(vec3(0, 0, 0)), angle(0) {
		shader = ShaderManager::instance()->getShader("lightShader");
	}

	GameObject(vec3& position, Hitbox *hitbox) : position(position), speed(vec3(0, 0, 0)), angle(0), hitbox(hitbox) {
		shader = ShaderManager::instance()->getShader("lightShader");
	}

	GameObject(vec3& position, char* modelName, Hitbox *hitbox) : position(position), speed(vec3(0, 0, 0)), angle(0), hitbox(hitbox) {
		shader = ShaderManager::instance()->getShader("lightShader");
		model = ModelManager::instance()->getModel(modelName);
		if (model == NULL)
			this->isActive = false;
	}

	GameObject(vec3& position, vec3& speed, float angle, char* modelName, Hitbox *hitbox) : position(position), speed(speed), angle(angle), hitbox(hitbox) {
		shader = ShaderManager::instance()->getShader("lightShader");
		model = ModelManager::instance()->getModel(modelName);
		if (model == NULL)
			this->isActive = false;
	}

	GameObject(vec3& position, char* modelName, char* shaderName) : position(position), speed(vec3(0, 0, 0)), angle(0) {
		shader = ShaderManager::instance()->getShader(shaderName);
		model = ModelManager::instance()->getModel(modelName);
		if (model == NULL)
			this->isActive = false;
	}

	virtual ~GameObject() {
		delete(hitbox);
	}

	vec3 getPosition() { return position; }

	void setPosition(vec3 p) { position = p; }

	vec3 getSpeed() { return speed; }

	void setSpeed(vec3 s) { speed = s; }

	int getAngle() { return angle; }

	void setAngle(int a) { angle = a; }

	Hitbox *getHitbox() { return hitbox; }
	virtual void updateHitbox() = 0;

	virtual void draw();
	virtual void update(float timeStep) = 0;

};