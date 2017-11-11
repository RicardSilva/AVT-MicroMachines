#pragma once
#include <GL/glew.h>
#include "AVTmathLib.h"
#include "Shader.h"
#include "TGA.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "Camera.h"

#define FLARE_ELEMENTS 5


class LensFlare {
	Shader* shader;
	GLuint TextureArray[5];
	ObjModel* model;
	float alphas[FLARE_ELEMENTS] = { 1.5f, 1.6f, 1.8f, 1.3f, 1.6f };
	vec4 colors[FLARE_ELEMENTS] = { vec4(1,1,1,1), vec4(1,1,1,1), vec4(1,1,1,1), vec4(1,1,1,1), vec4(1,1,1,1) };
	float sizes[FLARE_ELEMENTS] = { 0.2f, 0.3f, 0.1f, 0.2f, 0.3f };

public:
	LensFlare() {
		shader = ShaderManager::instance()->getShader("textureShader");
		model = ModelManager::instance()->getModel("flare");

		glGenTextures(FLARE_ELEMENTS, TextureArray);

		TGA_Texture(TextureArray, "textures/lensFlare/flare2.tga", 0);
		TGA_Texture(TextureArray, "textures/lensFlare/flare3.tga", 1);
		TGA_Texture(TextureArray, "textures/lensFlare/flare4.tga", 2);
		TGA_Texture(TextureArray, "textures/lensFlare/flare1.tga", 3);
		TGA_Texture(TextureArray, "textures/lensFlare/flare6.tga", 4);
	}
	virtual ~LensFlare() {

	}

	void draw(vec3 sunPosition);

};