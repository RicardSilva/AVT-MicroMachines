#include "LensFlare.h"

void LensFlare::draw(vec3 sunPosition) {
	
	int screenWidth = glutGet(GLUT_WINDOW_WIDTH);
	int screenHeight = glutGet(GLUT_WINDOW_HEIGHT);
	

	vec2 sunCoords = Camera::convertWorldToScreenSpace(sunPosition);
	pushMatrix(PROJECTION);
	loadIdentity(PROJECTION);
	pushMatrix(VIEW);
	loadIdentity(VIEW);
	//ortho(0, screenWidth, 0, screenHeight, -1, 1);
	if (sunCoords.x < 0 || sunCoords.x > 1 || sunCoords.y < 0 || sunCoords.y > 1) {
		popMatrix(PROJECTION);
		popMatrix(VIEW);
		return;
	}
	shader->use();
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	
	vec2 center = vec2(0.5f, 0.5f);
	loadIdentity(VIEW);
	float maxFlareDist = sqrt(center.x * center.x + center.y * center.y);
	float flareDist = sqrt((sunCoords.x - center.x) * (sunCoords.x - center.x)
	                      + (sunCoords.y - center.y) * (sunCoords.y - center.y));

	float distanceScale = (maxFlareDist - flareDist) / maxFlareDist;

	float dx = center.x + (center.x - sunCoords.x);
	float dy = center.y + (center.y - sunCoords.y);

	float elementDist;
	float px, py;
	float width, height;
	float alpha;
	for (int i = 0; i < FLARE_ELEMENTS; i++) {
		elementDist =- 6 + i * 3.0f;
		px = (1 - elementDist) * sunCoords.x + elementDist * dx;
		py = (1 - elementDist) * sunCoords.y + elementDist * dy;
	
		width = sizes[i] * distanceScale;

		if (width > 5)
			width = 5; 

		height = width *glutGet(GLUT_WINDOW_WIDTH) / glutGet(GLUT_WINDOW_HEIGHT);
	
		alpha = alphas[i] * distanceScale;

		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, TextureArray[i]);

		shader->loadTextureMode(2);
		shader->loadTexture(i);
		vec4 color = colors[i];
		color.w = alpha;
		shader->loadMatDiffuse(color);
	
		pushMatrix(MODEL);
		
		scale(MODEL, width, height, 1);
		translate(MODEL, -px, py, 1);
		shader->loadMatrices();

		for (auto mesh : model->meshes) {
			mesh->draw();
		}

		popMatrix(MODEL);
	}
	popMatrix(PROJECTION);
	popMatrix(VIEW);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	shader->unUse();
}
