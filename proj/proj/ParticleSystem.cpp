#include "ParticleSystem.h"

void ParticleSystem::update(double timeStep) {
	int i;
	timeStep = timeStep / 1000;	// convert ms to seconds


	for (i = 0; i<MAX_PARTICLES; i++)
	{
		particles[i].x += (timeStep*particles[i].vx);
		particles[i].y += (timeStep*particles[i].vy);
		particles[i].z += (timeStep*particles[i].vz);
		particles[i].vx += (timeStep*particles[i].ax);
		particles[i].vy += (timeStep*particles[i].ay);
		particles[i].vz += (timeStep*particles[i].az);
		if (particles[i].y <= 0)
			particles[i].reset();
	}
}

void ParticleSystem::draw() {
	vec4 particle_color = vec4();
	// draw fireworks particles

	glActiveTexture(GL_TEXTURE9);
	glBindTexture(GL_TEXTURE_2D, TextureArray[0]);
	glDisable(GL_DEPTH_TEST); 
	glDisable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader->use();
	shader->loadTextureMode(1);
	shader->loadTexture(9);

	for (int i = 0; i < MAX_PARTICLES; i++)
	{

		particle_color.x = particles[i].r;
		particle_color.y = particles[i].g;
		particle_color.z = particles[i].b;
		particle_color.w = particles[i].life;

		shader->loadMatDiffuse(particle_color);

		pushMatrix(MODEL);
		translate(MODEL, particles[i].x, particles[i].y, particles[i].z);

		shader->loadMatrices();

		for (auto mesh : model->meshes) {
			mesh->draw();
		}
			
		popMatrix(MODEL);
		
	}
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glBindTexture(GL_TEXTURE_2D, 0);
	shader->unUse();
}