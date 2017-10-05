#include "Car.h"

void Car::update(float timeStep) {}

void Car::draw() {
	//mesh->Draw();
	for(auto mesh: meshes)
		mesh.draw();


}