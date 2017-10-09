#include "Orange.h"
#include <cmath> 
void Orange::draw() {
	shader->use();

	pushMatrix(MODEL);
	loadIdentity(MODEL);

	translate(MODEL, position);
	//rotate(MODEL, rotationAngle, rotationAxle);
	scale(MODEL, 40, 40, 40);
	shader->loadMatrices();

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}


	popMatrix(MODEL);
	shader->unUse();
}

bool Orange::outOfBounds() {
	return (abs(position.x) > edgeX | (abs(position.z) > edgeZ));
}
void Orange::update(float timeStep) {
	timeStep = timeStep / 1000;	// convert ms to seconds

	float cosAngle = cos(degToRad(angle));	// convert from degrees to rads
	float sinAngle = sin(degToRad(angle));

	float posX = position.x;
	float posZ = position.z;

	float speedX = speed.x * acceleration * timeStep;
	float speedZ = speed.z * acceleration * timeStep;

	if (speedX > maxSpeed) speedX = maxSpeed;
	speed.x = speedX;

	if (speedZ > maxSpeed) speedZ = maxSpeed;
	speed.z = speedZ;

	// update position
	position.x = posX + speedX * cosAngle * timeStep;
	position.z = posZ + speedZ * sinAngle * timeStep;

	// update rotation angle
	rotationAngle = rotationAngle + speedX * 0.04;
	rotationAngle = rotationAngle % 360;

}