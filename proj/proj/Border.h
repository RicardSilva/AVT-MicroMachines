#ifndef __BORDER_H__
#define __BORDER_H__

#include "GameObject.h"


class Border : public GameObject {
	float width;
	float length;

public:

	Border(vec3 position, float width, float length);

	~Border() {}

	void draw() {
		hitbox->draw();
	}
	void update(float timeStep) {}

	void Border::updateHitbox() {}

};
#endif