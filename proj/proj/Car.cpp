#include "Car.h"

void Car::updateLights() {
	float posX;
	float posZ;

	//left
	//update light position
	posX = position.x + cos(degToRad(angle)) * 14.4 - sin(degToRad(angle)) * -5;
	posZ = position.z - sin(degToRad(angle))* -5 + cos(degToRad(angle) * 14.4);
	lights[0].position = vec4(posX, 10, posZ, 1);

	//update light direction
	lights[0].direction = vec4(cos(degToRad(angle)), 0, -sin(degToRad(angle)), 0);

	//right
	posX = position.x + cos(degToRad(angle)) * 14.4 - sin(degToRad(angle)) * 5;
	posZ = position.z - sin(degToRad(angle))* 5 + cos(degToRad(angle) * 14.4);
	lights[1].position = vec4(posX, 10, posZ, 1);
	
	lights[1].direction = vec4(cos(degToRad(angle)), 0, -sin(degToRad(angle)), 0);

	

	
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
	lights[0].draw();
	lights[1].draw();
}
void Car::draw() {
	shader->use();

	pushMatrix(MODEL);

	translate(MODEL, position);
	rotate(MODEL, angle, vec3(0, 1, 0));
	shader->loadMatrices();

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}
	
	popMatrix(MODEL);

	shader->unUse();
}

void Car::updateHitbox() { //TODO
	//getHitbox()->set(position.x + DISTANCE_BETWEEN_AXLES / 2.0 - (CAR_LENGTH * fabs(sin(getAngle() * PI / 180) + CAR_WIDTH * fabs(cos(getAngle() * PI / 180))) / 2,
	//				position.y - (CAR_LENGTH * fabs(cos(getAngle() * PI / 180)) + CAR_WIDTH * fabs(sin(getAngle() * PI / 180))) / 2,
	//				position.z - WHEEL_OUTER,
	//				position.x + DISTANCE_BETWEEN_AXLES / 2.0 + (CAR_LENGTH * fabs(sin(getAngle() * PI / 180) + CAR_WIDTH * fabs(cos(getAngle() * PI / 180))) / 2,
	//				position.y + (CAR_LENGTH * fabs(cos(getAngle() * PI / 180)) + CAR_WIDTH * fabs(sin(getAngle() * PI / 180))) / 2,
	//				position.z + CAR_HEIGHT + CAR_HEIGHT);
	getHitbox()->set(position.x - (CAR_LENGTH * fabs(sin(getAngle() * PI / 180)) + CAR_WIDTH * fabs(cos(getAngle() * PI / 180))) / 2,
						position.y,
						position.z - (CAR_LENGTH * fabs(cos(getAngle() * PI / 180)) + CAR_WIDTH * fabs(sin(getAngle() * PI / 180))) / 2,
						position.x + (CAR_LENGTH * fabs(sin(getAngle() * PI / 180)) + CAR_WIDTH * fabs(cos(getAngle() * PI / 180))) / 2,
						position.y,
						position.z + (CAR_LENGTH * fabs(cos(getAngle() * PI / 180)) + CAR_WIDTH * fabs(sin(getAngle() * PI / 180))) / 2);

}