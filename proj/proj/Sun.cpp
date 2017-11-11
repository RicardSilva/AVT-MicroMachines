#include "Sun.h"

void Sun::draw(vec3 cam) {
	shader->use();
	float pos[3] = { position.x , position.y, position.z };
	float camPos[3] = { cam.x , cam.y, cam.z };


	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	pushMatrix(MODEL);
	loadIdentity(MODEL);
	translate(MODEL, position);
	scale(MODEL, 50, 50, 50);

	l3dBillboardCylindricalBegin(camPos, pos);

	shader->loadMatrices();
	shader->loadTextureMode(1);
	shader->loadMatDiffuse(vec4(1, 0.6, 0, 1));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureArray[0]);

	shader->loadTexture(0);
	for (auto mesh : model->meshes) {
		mesh->draw();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shader->unUse();

	popMatrix(MODEL);
}