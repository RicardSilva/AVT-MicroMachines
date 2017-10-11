#include "Butter.h"
void Butter::draw() {
	shader->use();

	pushMatrix(MODEL);
	loadIdentity(MODEL);

	translate(MODEL, position);
	rotate(MODEL, angle, vec3(0, 1, 0));
	scale(MODEL, 20, 20, 20);
	shader->loadMatrices();

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}


	popMatrix(MODEL);
	shader->unUse();
}

void Butter::update(float timeStep) {
	angle += 1;
}