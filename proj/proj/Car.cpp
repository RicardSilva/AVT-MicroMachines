#include "Car.h"

void Car::updateLights() {
	float posX;
	float posZ;

	//left
	//update light position
	posX = 10 * cos(degToRad(angle)) + -4.5 * sin(degToRad(angle)) + position.x;
	posZ = -4.5 * cos(degToRad(angle)) - 10 * sin(degToRad(angle)) + position.z;
	leftLight.position = vec4(posX, 1, posZ, 1);

	//update light direction
	leftLight.direction = vec4(cos(degToRad(angle)), -0.1, -sin(degToRad(angle)), 0);

	//right
	posX = 10 * cos(degToRad(angle)) + 4.5 * sin(degToRad(angle)) + position.x;
	posZ = 4.5 * cos(degToRad(angle)) - 10 * sin(degToRad(angle)) + position.z;
	rightLight.position = vec4(posX, 1, posZ, 1);
	
	rightLight.direction = vec4(cos(degToRad(angle)), -0.1, -sin(degToRad(angle)), 0);

	

	
}
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
	position.x = posX + speedX * cosAngle * timeStep;
	position.z = posZ + speedZ * -sinAngle * timeStep;


	updateLights();

	updateHitbox();
}

void Car::drawLights() {
	leftLight.draw();
	rightLight.draw();
}
void Car::draw() {
	glCullFace(GL_FRONT);
	//glDisable(GL_CULL_FACE);
	pushMatrix(MODEL);

	translate(MODEL, position);
	rotate(MODEL, angle, vec3(0, 1, 0));
	shader->loadMatrices();

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}
	
	popMatrix(MODEL);


	glCullFace(GL_BACK);

	pushMatrix(MODEL);

	translate(MODEL, position);
	rotate(MODEL, angle, vec3(0, 1, 0));
	shader->loadMatrices();

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}

	popMatrix(MODEL);



	hitbox->draw();


}

void Car::updateHitbox() {
	float sinAngle = fabs(sin(getAngle() * PI / 180));
	float cosAngle = fabs(cos(getAngle() * PI / 180));
	getHitbox()->set(position.x - (CAR_LENGTH * cosAngle + CAR_WIDTH * sinAngle) / 2,
						position.y - CAR_HEIGHT / 2,
						position.z - (CAR_LENGTH * sinAngle + CAR_WIDTH * cosAngle) / 2,
						position.x + (CAR_LENGTH * cosAngle + CAR_WIDTH * sinAngle) / 2,
						position.y + CAR_HEIGHT / 2,
						position.z + (CAR_LENGTH * sinAngle + CAR_WIDTH * cosAngle) / 2);

}
void Car::restart(vec3& pos) {
	position = pos;
	angle = 0;
	speed = vec3(0, 0, 0);
}
