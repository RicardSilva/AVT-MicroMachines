#include "DirectionalLight.h"

void DirectionalLight::draw() {

	shader->use();
	shader->loadDirectionalLight(*this);
	shader->unUse();

}