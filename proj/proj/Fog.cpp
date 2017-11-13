#include "Fog.h"
void Fog::on() {
	shader->use();
	shader->loadFoggy(true);
}
void Fog::off() {
	shader->use();
	shader->loadFoggy(false);
}