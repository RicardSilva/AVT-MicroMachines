#include "Billboard.h"

class Sun : public Billboard {

public:
	Sun(vec3 position, char* texName, char* shaderName, char* modelName) : Billboard(position, texName, shaderName, modelName) {
	}
	virtual ~Sun() {}

	void draw(vec3 cam);
};