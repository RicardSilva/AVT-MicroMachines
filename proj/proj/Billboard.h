#pragma once
#include <GL/glew.h>
#include "AVTmathLib.h"
#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "TGA.h"

class Billboard : public GameObject { //TODO ADD HITBOX
protected:
	GLuint TextureArray[1];

public:
	Billboard(vec3& position, char* texName) : GameObject(position, "billboard", "lightShader")
	{
		glGenTextures(1, TextureArray);
		TGA_Texture(TextureArray, texName, 0);
	}
	Billboard(vec3& position, char* texName, char* shaderName, char* modelName) : GameObject(position, modelName, shaderName) {
		glGenTextures(1, TextureArray);
		TGA_Texture(TextureArray, texName, 0);
	}

	virtual ~Billboard() {}

	void draw(vec3 cam);

	void update(float timeStep) {};
	void updateHitbox() {};

	void l3dBillboardCylindricalBegin(float *cam, float *worldPos);
};
