#include "Car.h"

void Car::update(float timeStep) {}

void Car::draw() {
	shader->use();

	pushMatrix(MODEL);
	loadIdentity(MODEL);

	translate(MODEL, position);
	scale(MODEL, 6, 5, 5);
	shader->loadMatrices();

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}


	popMatrix(MODEL);
	shader->unUse();
}