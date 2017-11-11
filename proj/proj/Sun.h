#include "Billboard.h"

class Sun : public Billboard {

public:
	Sun(vec3 position, char* texName, char* shaderName) : Billboard(position, texName, shaderName, "flare")
	{ }

	virtual ~Sun() {}

	void draw(vec3 cam);
};