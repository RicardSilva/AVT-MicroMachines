#include "Butter.h"
void Butter::draw() {
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

void Butter::update(float timeStep) {
	timeStep = timeStep / 1000;	// convert ms to seconds

	float speedX = speed.x;
	float speedZ = speed.z;

	if (speedX == 0 && speedZ == 0) { // do nothing
		return;
	}

	float cosAngle = cos(angle * PI / 180);	// convert from degrees to rads
	float sinAngle = sin(angle * PI / 180);

	float posX = position.x;
	float posZ = position.z;



	if (speedX > 0) {
		speedX = speedX - inercia * timeStep;
		if (speedX < 0)
			speedX = 0;
		speed.x = speedX;
	}
	else if (speedX < 0) {
		speedX = speedX + inercia * timeStep;
		if (speedX > 0)
			speedX = 0;
		speed.x = speedX;
	}

	if (speedZ > 0) {
		speedZ = speedX - inercia * timeStep;
		if (speedZ < 0)
			speedZ = 0;
		speed.y = speedZ;
	}
	else if (speedZ < 0) {
		speedZ = speedZ + inercia * timeStep;
		if (speedZ > 0)
			speedZ = 0;
		speed.z = speedZ;
	}

	// update position

	position.x = posX + speedX * cosAngle * timeStep;
	position.z = posZ + speedZ * -sinAngle * timeStep;

	updateHitbox();
}

void Butter::updateHitbox() {
	getHitbox()->set(position.x - BUTTER_WIDTH / 2.0,
		position.y - BUTTER_HEIGHT / 2.0,
		position.z - BUTTER_LENGTH / 2,
		position.x + BUTTER_WIDTH / 2.0,
		position.y + BUTTER_HEIGHT / 2.0,
		position.z + BUTTER_LENGTH / 2
	);
}