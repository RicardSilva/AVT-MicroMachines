#include "Orange.h"
#include <cmath> 
void Orange::draw() {
	shader->use();

	pushMatrix(MODEL);
	loadIdentity(MODEL);

	translate(MODEL, position);
	scale(MODEL,50, 50, 50);
	shader->loadMatrices();

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}


	popMatrix(MODEL);
	shader->unUse();
}
void Orange::reset() {
	position.x = std::rand() % 400;
	position.z = std::rand() % 400;
	angle=std::rand() % 360;
}
bool Orange::outOfBounds() {
	return (abs(position.x) > edgeX | (abs(position.z) > edgeZ));
}
void Orange::update(float timeStep) {
	timeStep = timeStep / 1000;
	float speedX = speed.x;
	float speedZ = speed.z;

	absSpeed += acceleration * timeStep;
	
	speedX = cos(angle) * absSpeed;
	speedZ = sin(angle) * absSpeed;
	
	speed.x = speedX;
	speed.z = speedZ;

	position.x += speedX * timeStep;
	position.z += speedZ * timeStep;
	if (outOfBounds()) reset();


}