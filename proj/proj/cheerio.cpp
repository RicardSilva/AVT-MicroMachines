#include "Cheerio.h"

void Cheerio::draw() {
	shader->use();

	pushMatrix(MODEL);
	loadIdentity(MODEL);

	translate(MODEL, position);
	scale(MODEL, 15, 15, 15);
	shader->loadMatrices();

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}


	popMatrix(MODEL);
	shader->unUse();
}