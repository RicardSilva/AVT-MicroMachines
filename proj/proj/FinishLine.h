#pragma once
#include "Border.h"
#include "TGA.h"
class FinishLine : public Border {
	GLuint TextureArray[1];
public:
	FinishLine(vec3 position, float width, float length) : Border(position, width, length, "finish") { 
	
		glGenTextures(1, TextureArray);
		TGA_Texture(TextureArray, "textures/finish.tga", 0);
	}

	virtual void draw() {
		pushMatrix(MODEL);
		loadIdentity(MODEL);
		translate(MODEL, position);
		glDisable(GL_DEPTH_TEST);

		shader->loadMatrices();

		shader->enableTextures();
		shader->loadTextureMode(2);

		glActiveTexture(GL_TEXTURE11);
		glBindTexture(GL_TEXTURE_2D, TextureArray[0]);

		shader->loadTree(11);
		shader->loadMatDiffuse(vec4(1, 1, 1, 1));
		for (auto mesh : model->meshes) {
			mesh->draw();
		}

		shader->disableTextures();
		glBindTexture(GL_TEXTURE_2D, 0);

		glEnable(GL_DEPTH_TEST);

		popMatrix(MODEL);
		hitbox->draw();
	}
};