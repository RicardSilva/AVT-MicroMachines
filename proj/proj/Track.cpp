#include "Track.h"

void Track::loadFromFile(std::string& file) {
	int x = 0;
	int z = 100;
	char a;
	int i;
	fstream myfile;
	myfile.open(file);
	
	while (x < 140 && z > 0) {
		
		myfile >> a;
		i = a - '0';
		if (i == 1) {
			//new cheerio
			cheerios.push_back(new Cheerio(vec3((x * 10 - 700), 0, -(z * 10 - 500))));
		}
		else if (i == 2) {
			//new candle
			pointLights.push_back(new PointLight(vec4((x * 10 - 700), 0, -(z * 10 - 500), 0), vec3(1, 0.3, 0.3), 1));
		}
		else if (i == 3) {
			//new butter
			butters.push_back(new Butter(vec3((x * 10 - 700), 5, -(z * 10 - 500))));
		}
		else if (i == 4) {
			setStartingPosition(vec3((x * 10 - 700), 0, -(z * 10 - 500)));
		}
		x++;
		if (x == 140) {
			x = 0;
			z--;
		}
	}

}

void Track::attemptToSpawnOrange() {
	int randomNumber;
	int trackPerimeter = 2 * (TRACK_WIDTH + 50) + 2 *(TRACK_HEIGHT + 50);
	int x = -TRACK_WIDTH / 2- 50; // bottom left corner
	int z = -TRACK_HEIGHT / 2 - 50;
	float speed = 0;
	float angle = 0;	// degrees
	Orange* orange;
	float cosAngle;	// convert from degrees to rads
	float sinAngle;
	int axleAngle;

	if (orangeCounter >= MAX_ORANGES) { return; } 

	// randomly select position, angle and speed for the new orange 
	randomNumber = rand() % trackPerimeter + 1;	// number in the range of 1 to track_perimeter

													// COMPUTES RANDOM POSITION using perimeter
	if (randomNumber < 1500) {
		x = x + randomNumber;
	}
	else if (randomNumber < 2600) {
		x = x + 1500;
		z = z + randomNumber - 1500;
	}
	else if (randomNumber < 4100) {
		x = x + 4100 - (randomNumber);
		z = z + 1100;
	}
	else if (randomNumber <= 5200) {
		z = z + 5200 - (randomNumber);
	}

	// SELECT RANDOM ANGLE 
	angle = asin(z / (sqrt(x * x + z * z)));	// normalize y coordinate
	angle = radToDeg(angle);	// convert from rads to degrees

							// computes angle from spawn point to origin (0, 0)
	if (x >= 0 && z >= 0) {	// first quadrant
		angle = 180 + angle;
	}
	else if (x < 0 && z >= 0) {	// second quadrant
		angle = 360 - angle;
	}
	else if (x < 0 && z < 0) {	// third quadrant
		angle = -angle;
	}
	else {	// forth quadrant
		angle = 180 + angle;
	}

	angle = angle + rand() % 80 - 40;	// randomize angle

	speed = rand() % 20 + ORANGE_BASE_SPEED;	// SELECT RANDOM SPEED dependent on time since game started

												// compute rotation axle angle
	axleAngle = angle + 90;	// axle is perpendicular to direction of movement
	axleAngle = axleAngle % 360;

	cosAngle = cos(degToRad(axleAngle));	// convert from degrees to rads
	sinAngle = sin(degToRad(axleAngle));

	Orange* o = new Orange(vec3(x, 0, z), vec3(speed, 0, speed), angle, vec3(cosAngle, 0, sinAngle));
	o->isActive = true;
	oranges.push_back(o);
	orangeCounter++;
}

void Track::update(float timeStep) {
	for (auto cheerio : cheerios)
		cheerio->update(timeStep);
	for (auto butter : butters)
		butter->update(timeStep);
	for (auto orange : oranges) {
		if (orange->isActive) {
			orange->update(timeStep);
			if (orange->outOfBounds()) {
				orange->isActive = false;
				orangeCounter--;
			}
		}
	}
}

void Track::drawLights() {
	dirLight.draw();
	//for (auto light : pointLights)
	//	light->draw();
}
void Track::draw() {
	
	shader->use();

	pushMatrix(MODEL);
	
	loadIdentity(MODEL);
	translate(MODEL, position);

	shader->loadMatrices();

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}

	
	shader->unUse();

	for (auto cheerio : cheerios)
		cheerio->draw();
	for (auto butter : butters)
		butter->draw();
	for (auto orange : oranges) {
		if (orange->isActive)
			orange->draw();
	}

	popMatrix(MODEL);
}