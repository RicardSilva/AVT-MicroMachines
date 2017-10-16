#include "SpotLight.h"

void SpotLight::draw() {
	shader->use();
	shader->loadSpotLight(*this);
	shader->unUse();

}