#include "GameObject.h"

void GameObject::draw(){
	shader->use();

	pushMatrix(MODEL);
	loadIdentity(MODEL);
	
	translate(MODEL, position);
	scale(MODEL, vec3(20, 1, 20));
	shader->loadMatrices();

	for (auto mesh : meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}


	popMatrix(MODEL);
	shader->unUse();
}