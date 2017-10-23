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

	
	vec3 speed;
	int angle;

public:
	bool isActive = true;
	vec3 position;

	GameObject() {}
	GameObject(vec3& position, vec3& speed, float angle)
		: position(position), speed(speed), angle(angle) {
		shader = ShaderManager::instance()->getShader("lightShader");
	}
	GameObject(vec3& position) : position(position), speed(vec3(0, 0, 0)), angle(0) {
		shader = ShaderManager::instance()->getShader("lightShader");
	}
	GameObject(vec3& position, vec3& speed, float angle, Hitbox *hitbox) : position(position), speed(speed), angle(angle), hitbox(hitbox) {
		shader = ShaderManager::instance()->getShader("lightShader");
	}
	GameObject(vec3& position, Hitbox *hitbox) : position(position), speed(vec3(0, 0, 0)), angle(0), hitbox(hitbox) {
		shader = ShaderManager::instance()->getShader("lightShader");
	}
	virtual ~GameObject() {}

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