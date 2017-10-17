#ifndef __BORDER_H__
#define __BORDER_H__

#include "GameObject.h"


class Border : public GameObject {
	float _width;
	float _length;

public:

	Border(vec3 position, float width, float length);

	~Border() {}

	void draw() {}
	void update(float timeStep) {}

};
#endif