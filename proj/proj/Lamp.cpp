#include "Lamp.h"

void Lamp::drawLights (){
	light.draw();
}

void Lamp::draw() {
	shader->use();

	pushMatrix(MODEL);
	loadIdentity(MODEL);

	translate(MODEL, position);
	shader->loadMatrices();

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}


	popMatrix(MODEL);
	shader->unUse();
}

void Lamp::update(float timeStep) { //TODO

	updateHitbox();
}

void Lamp::updateHitbox() {
	getHitbox()->set(position.x - LAMP_LENGTH / 2.0,
		position.y - LAMP_HEIGHT / 2.0,
		position.z - LAMP_WIDTH / 2.0,
		position.x + LAMP_LENGTH / 2.0,
		position.y + LAMP_HEIGHT / 2.0,
		position.z + LAMP_WIDTH / 2.0
	);
}