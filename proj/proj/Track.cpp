#include "Track.h"

void Track::importFromFile(std::string& file) {
	int x = 0;
	int y = 100;
	char a;
	int i;
	fstream myfile;
	myfile.open(file);
	
	while (x < 140 && y > 0) {
		
		myfile >> a;
		i = a - '0';
		if (i == 1) {
			//new cheerio
			cheerios.push_back(new Cheerio(vec3((x * 10 - 700), 0 , -(y * 10 - 500))));
		}
		else if (i == 2) {
			//new candle
			
		}
		else if (i == 3) {
			//new butter
			butters.push_back(new Butter(vec3((x * 10 - 700), 5, -(y * 10 - 500))));
		}
		else if (i == 4) {
			setStartingPosition(vec3((x * 10 - 700), 0, -(y * 10 - 500)));
		}
		x++;
		if (x == 140) {
			x = 0;
			y--;
		}
	}

}

void Track::update(float timeStep) {
	for (auto cheerio : cheerios)
		cheerio->update(timeStep);
	for (auto butter : butters)
		butter->update(timeStep);
	for (auto orange : oranges)
		orange->update(timeStep);
}

void Track::draw() {

	shader->use();

	pushMatrix(MODEL);
	loadIdentity(MODEL);
	translate(MODEL, position);
	scale(MODEL, 700, 0.1, 500);

	shader->loadMatrices();

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}


	popMatrix(MODEL);
	shader->unUse();

	for (auto cheerio : cheerios)
		cheerio->draw();
	for (auto butter : butters)
		butter->draw();
	for (auto orange : oranges)
		orange->draw();
}