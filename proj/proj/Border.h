#ifndef __BORDER_H__
#define __BORDER_H__

#include "GameObject.h"


class Border : public GameObject {
	float width;
	float length;

public:

	Border(vec3 position, float width, float length) : width(width), length(length),
		GameObject(position, new Hitbox(vec3(position.x - width, 0, position.z - length),
			vec3(position.x + width, 20, position.z + length)))
	{ }

	~Border() {}

	void draw();

	void update(float timeStep) {}

	void Border::updateHitbox() {}

};
#endif