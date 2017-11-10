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
		if (i == 0) {
			// do nothing
		}
		else if (i == 1) {
			//new cheerio
			cheerios.push_back(new Cheerio(vec3((x * 10 - 700), 0, -(z * 10 - 500))));
		}
		else if (i == 2) {
			//new candle
			lamps.push_back(new Lamp(vec3((x * 10 - 700), 0, -(z * 10 - 500))));
		}
		else if (i == 3) {
			//new butter
			butters.push_back(new Butter(vec3((x * 10 - 700), 0, -(z * 10 - 500))));
		}
		else if (i == 4) {
			startingPosition = vec3((x * 10 - 700), 0, -(z * 10 - 500));
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
	angle = -asin(z / (sqrt(x * x + z * z)));	// normalize y coordinate
	angle = radToDeg(angle);	// convert from rads to degrees

							// computes angle from spawn point to origin (0, 0)
	if (x >= 0 && z < 0) {	// first quadrant
		angle = 180 + angle;
	}
	else if (x < 0 && z < 0) {	// second quadrant
		angle = 360 - angle;
	}
	else if (x < 0 && z >= 0) {	// third quadrant
		angle = -angle;
	}
	else {	// forth quadrant
		angle = 180 + angle;
	}

	angle = angle + rand() % 80 - 40;	// randomize angle

	speed = rand() % 20 + orangeStartingSpeed;	

												// compute rotation axle angle
	axleAngle = angle + 90;	// axle is perpendicular to direction of movement
	axleAngle = axleAngle % 360;

	cosAngle = cos(degToRad(axleAngle));	// convert from degrees to rads
	sinAngle = sin(degToRad(axleAngle));

	Orange* o = new Orange(vec3(x, 0, z), vec3(speed, 0, speed), angle, vec3(cosAngle, 0, -sinAngle));
	o->isActive = true;
	oranges.push_back(o);
	orangeCounter++;
}
void Track::increaseOrangeSpeed() {
	orangeStartingSpeed += 125;
	for (auto orange : oranges)
	{
		orange->increaseSpeed();
	}
}

void Track::update(float timeStep) {
	for (auto cheerio : cheerios) {
		if (cheerio->isActive)
			cheerio->update(timeStep);
	}
	for (auto butter : butters) {
		if (butter->isActive)
			butter->update(timeStep);
	}
	for (std::vector<int>::size_type i = 0; i < oranges.size(); i++) {
		Orange* orange = oranges[i];
		if (orange->isActive) {
			orange->update(timeStep);
			if (orange->outOfBounds()) {
				oranges.erase(oranges.begin() + i);
				delete(orange);
				orangeCounter--;
			}
		}
	}
}

void Track::drawLights() {
	dirLight.draw();
	for (auto lamp : lamps)
		lamp->drawLights();
}
void Track::draw(vec3 cam) {
	

	pushMatrix(MODEL);
	
	translate(MODEL, position);

	shader->loadMatrices();

	//load textures
	shader->enableTextures();
	shader->loadTextureMode(0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextureArray[1]);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, TextureArray[2]);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, TextureArray[3]);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_2D, TextureArray[4]);

	shader->loadWoodDiffuse(0);
	shader->loadWoodSpecular(1);
	shader->loadBambooDiffuse(2);
	shader->loadBambooSpecular(3);
	shader->loadMask(4);

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}

	
	shader->disableTextures();
	glBindTexture(GL_TEXTURE_2D, 0);

	shader->loadMaterial(cheerios[0]->model->meshes[0]->MeshMaterial);
	for (auto cheerio : cheerios)
		if (cheerio->isActive)
		cheerio->draw();
	for (auto butter : butters)
		if (butter->isActive)
		butter->draw();
	for (auto orange : oranges) {
		if (orange->isActive)
			orange->draw();
	}
	for (auto lamp : lamps) {
		lamp->draw();
	}
	for (auto border : borders) {
		border->draw();
	}
	finishLine->draw();
	billboard->draw(cam);

	popMatrix(MODEL);
}

void Track::restart() {
	std::string file = std::string(TRACK_FILE);
	int x = 0;
	int z = 100;
	char a;
	int i;
	fstream myfile;
	myfile.open(file);

	cheerios.clear();
	butters.clear();
	oranges.clear();
	orangeCounter = 0;
	orangeStartingSpeed = 125;
	while (x < 140 && z > 0) {

		myfile >> a;
		i = a - '0';
		if (i == 0) {
			// do nothing
		}
		else if (i == 1) {
			//new cheerio
			cheerios.push_back(new Cheerio(vec3((x * 10 - 700), 0, -(z * 10 - 500))));
		}
		else if (i == 2) {
		}
		else if (i == 3) {
			//new butter
			butters.push_back(new Butter(vec3((x * 10 - 700), 0, -(z * 10 - 500))));
		}
		else if (i == 4) {
		}
		x++;
		if (x == 140) {
			x = 0;
			z--;
		}
	}
}