#include "Fog.h"
void Fog::on() {
	this->shader->loadFoggy(true);
}
void Fog::off() {
	this->shader->loadFoggy(false);
}