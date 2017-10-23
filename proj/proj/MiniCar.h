#pragma once
#include "vec3.h"
#include "AVTmathLib.h"
#include "GameObject.h"

#define PI 3.14

#define CAR_WIDTH 16.2
#define CAR_LENGTH 30
#define CAR_HEIGHT 11.7

class MiniCar : public GameObject {


public:
	MiniCar(vec3& position)
		: GameObject(position, new Hitbox(vec3(position.x - CAR_LENGTH / 2, position.y - CAR_HEIGHT / 2, position.z - CAR_WIDTH / 2),
			vec3(position.x + CAR_LENGTH / 2, position.y + CAR_HEIGHT / 2, position.z + CAR_WIDTH / 2))) {

		model = ModelManager::instance()->getModel("car_mini");
		if (model == NULL)
			this->isActive = false;


	}
	virtual ~MiniCar() {}

	void draw() {
		pushMatrix(MODEL);

		translate(MODEL, position);
		rotate(MODEL, angle, vec3(0, 1, 0));
		shader->loadMatrices();

		for (auto mesh : model->meshes) {
			shader->loadMaterial(mesh->MeshMaterial);
			mesh->draw();
		}

		popMatrix(MODEL);
	}

	void update(float timeStep) {}
	void updateHitbox() {}
};
