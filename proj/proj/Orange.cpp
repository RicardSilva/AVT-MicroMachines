#include "Orange.h"
#include <cmath> 
void Orange::draw() {

	pushMatrix(MODEL);
	loadIdentity(MODEL);

	
	translate(MODEL, vec3(0,30,0) +  position); 
	rotate(MODEL, rotationAngle, rotationAxle);

	shader->loadMatrices();

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}

	popMatrix(MODEL);
	hitbox->draw();
}

bool Orange::outOfBounds() {
	return (abs(position.x) > edgeX | (abs(position.z) > edgeZ));
}
void Orange::increaseSpeed() {
	speed.x += 20;
	speed.z += 20;

	if (speed.x > 400)
		speed.x = 400;
	if (speed.z > 400)
		speed.z = 400;
	
}

void Orange::update(float timeStep) {
	timeStep = timeStep / 1000;	// convert ms to seconds

	float cosAngle = cos(degToRad(angle));	// convert from degrees to rads
	float sinAngle = sin(degToRad(angle));

	float posX = position.x;
	float posZ = position.z;


	// update position
	position.x = posX + speed.x * cosAngle * timeStep;
	position.z = posZ + speed.z * -sinAngle * timeStep;

	// update rotation angle
	rotationAngle = rotationAngle + speed.x * 0.04;
	rotationAngle = rotationAngle % 360;

	updateHitbox();
}

void Orange::updateHitbox() {
	getHitbox()->set(position.x - ORANGE_RADIUS, position.y - ORANGE_RADIUS + 30, position.z - ORANGE_RADIUS,
		position.x + ORANGE_RADIUS, position.y + ORANGE_RADIUS + 30, position.z + ORANGE_RADIUS);
}