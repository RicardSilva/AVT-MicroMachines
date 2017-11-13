#pragma once
#include <GL/glew.h>
#include "AVTmathLib.h"
#include "Shader.h"
#include "TGA.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "vec4.h"

#define MAX_PARTICLES 1000

struct Particle {
	float	life;		// vida
	float	fade;		// fade
	vec4    color;
	GLfloat x, y, z;    // posicao
	GLfloat vx, vy, vz; // velocidade 
	GLfloat ax, ay, az; // aceleracao

	Particle() {
		float randomNumber = rand() % 1500 + 1;
		float randomNumber2 = rand() % 25 + 1;
		float randomNumber3 = rand() % 1100 + 1;
		float randomNumber4 = rand() % 90 + 70;
		x = -700.0f + randomNumber;
		y = 50 + randomNumber2;
		z = -500.0f + randomNumber3;
		vx = 0;
		vy = -randomNumber4;
		vz = 0;
		ax = 20.0f; /* simular um pouco de vento */
		ay = -10.0f; /* simular a aceleração da gravidade */
		az = 0.0f;

		color = vec4(0.5, 0.7, 0.8, 1.0);
	}

	void reset() {
		float randomNumber = rand() % 1500 + 1;
		float randomNumber2 = rand() % 25 + 1;
		float randomNumber3 = rand() % 1100 + 1;
		float randomNumber4 = rand() % 90 + 70;
		x = -700.0f + randomNumber;
		y = 50 + randomNumber2;
		z = -500.0f + randomNumber3;
		vx = 0;
		vy = -randomNumber4;
		vz = 0;
		ax = 20.0f; /* simular um pouco de vento */
		ay = -10.0f; /* simular a aceleração da gravidade */
		az = 0.0f;
	}
} ;

class ParticleSystem {
	Shader* shader;
	Particle particles[MAX_PARTICLES];
	GLuint TextureArray[1];
	ObjModel* model;

public:
	ParticleSystem() {
		shader = ShaderManager::instance()->getShader("textureShader");
		model = ModelManager::instance()->getModel("particle");
		glGenTextures(1, TextureArray);
		TGA_Texture(TextureArray, "textures/particle2.tga", 0);

		for (int i = 0; i < MAX_PARTICLES; i++) {
			particles[i] = Particle();
		}
	}
	virtual ~ParticleSystem() {}

	void update(double timeStep);
	void draw();
};