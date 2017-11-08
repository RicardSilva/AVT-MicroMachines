#pragma once
#include <GL/glew.h>
#include "AVTmathLib.h"
#include "Shader.h"
#include "TGA.h"
#include "ModelManager.h"
#include "ShaderManager.h"


class LensFlare {
	Shader* shader;
	GLuint TextureArray[6];
	ObjModel* model;

	LensFlare() {

		glGenTextures(6, TextureArray);
		TGA_Texture(TextureArray, "textures/lensFlare/flare1.tga", 0);
		TGA_Texture(TextureArray, "textures/lensFlare/flare2.tga", 1);
		TGA_Texture(TextureArray, "textures/lensFlare/flare3.tga", 2);
		TGA_Texture(TextureArray, "textures/lensFlare/flare4.tga", 3);
		TGA_Texture(TextureArray, "textures/lensFlare/flare5.tga", 4);
		TGA_Texture(TextureArray, "textures/lensFlare/flare6.tga", 5);
	}
	virtual ~LensFlare() {

	}


};