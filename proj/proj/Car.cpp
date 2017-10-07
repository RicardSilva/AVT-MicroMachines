#include "Car.h"

void Car::update(float timeStep) {
	timeStep = timeStep / 1000;	// convert ms to seconds

	float cosAngle;
	float sinAngle;

	float posX = position.x;
	float posZ = position.z;

	float speedX = speed.x;
	float speedZ = speed.z;

	// update angle
	if (turnLeft) {
		angle += angleInc; 
		angle = angle % 360;
	}
	else if (turnRight) {
		angle -= angleInc;
		angle = angle % 360;
	}

	cosAngle = cos(angle * PI / 180);	// convert from degrees to rads
	sinAngle = sin(angle * PI / 180);


	// update speed
	if (goForward) {

		speedX = speedX + acceleration * timeStep;
		if (speedX > maxSpeed) {
			speedX = maxSpeed;
		}
		speed.x = speedX;

		speedZ = speedZ + acceleration * timeStep;
		if (speedZ > maxSpeed) {
			speedZ = maxSpeed;
		}
		speed.z = speedZ;

	}

	else if (!goForward && !goBack) {

		if (speedX > 0) {
			speedX = speedX - inercia * timeStep;
			if (speedX < 0) {
				speedX = 0;
			}
			speed.x = speedX;
		}
		else if (speedX < 0) {
			speedX = speedX + inercia * timeStep;
			if (speedX > 0) {
				speedX = 0;
			}
			speed.x = speedX;
		}

		if (speedZ > 0) {
			speedZ = speedZ - inercia * timeStep;
			if (speedZ < 0) {
				speedZ = 0;
			}
			speed.z = speedZ;
		}
		else if (speedZ < 0) {
			speedZ = speedZ + inercia * timeStep;
			if (speedZ > 0) {
				speedZ = 0;
			}
			speed.z = speedZ;
		}

	}

	else if (goBack) {

		if (speedX > maxBackwardsSpeed) {
			speedX = speedX - backwardsAcceleration * timeStep;
			if (speedX < maxBackwardsSpeed) {
				speedX = maxBackwardsSpeed;
			}
			speed.x = speedX;
		}

		if (speedZ > maxBackwardsSpeed) {
			speedZ = speedZ - backwardsAcceleration * timeStep;
			if (speedZ < maxBackwardsSpeed) {
				speedZ = maxBackwardsSpeed;
			}
			speed.z = speedZ;
		}

	}

	// update position
	position.x = posX + speedX * sinAngle * timeStep;
	position.z = posZ + speedZ * cosAngle * timeStep;
}

void Car::draw() {
	shader->use();

	pushMatrix(MODEL);
	loadIdentity(MODEL);

	translate(MODEL, position);
	rotate(MODEL, angle, vec3(0, 1, 0));
	scale(MODEL, 10, 10, 8);
	shader->loadMatrices();

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}


	popMatrix(MODEL);
	shader->unUse();
}