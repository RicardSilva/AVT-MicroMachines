#include "Car.h"

void Car::update(float timeStep) {}

void Car::draw() {

	pushMatrix(MODEL);
	translate(MODEL, position);
	mesh->Draw();
	popMatrix(MODEL);


}