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

void Cheerio::update(float timeStep) { //TODO

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
		speed.z = speedZ;
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

	// update hitbox
	getHitbox()->set(position.x - CHEERIO_OUTER - (CHEERIO_OUTER - CHEERIO_INNER),
					position.y - CHEERIO_OUTER - (CHEERIO_OUTER - CHEERIO_INNER),
					position.z - (CHEERIO_OUTER - CHEERIO_INNER),
					position.x + CHEERIO_OUTER + (CHEERIO_OUTER - CHEERIO_INNER),
					position.y + CHEERIO_OUTER + (CHEERIO_OUTER - CHEERIO_INNER),
					position.z + CHEERIO_OUTER - CHEERIO_INNER
	);
}