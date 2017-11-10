#pragma once
#include <GL/glew.h>
#include "AVTmathLib.h"
#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"
#include "ShaderManager.h"
#include "TGA.h"

class Billboard : public GameObject {
	GLuint TextureArray[1];

public:
	Billboard(vec3& position) : GameObject(position) {
		model = ModelManager::instance()->getModel("billboard");
		if (model == NULL)
			this->isActive = false;

		glGenTextures(1, TextureArray);
		TGA_Texture(TextureArray, "textures/christmastree.tga", 0);
	}

	virtual ~Billboard() {}

	void draw(vec3 cam);

	void update(float timeStep) {};
	void updateHitbox() {};

	void l3dBillboardCylindricalBegin(float *cam, float *worldPos);
};
