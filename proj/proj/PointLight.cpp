#include "PointLight.h"

void PointLight::draw() {
	shader->use();
	shader->loadPointLight(*this);
	shader->unUse();
}