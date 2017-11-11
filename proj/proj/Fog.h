#pragma once
#include <GL/glew.h>
#include "AVTmathLib.h"
#include "LightShader.h"
#include "TGA.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "vec4.h"
class Fog {
	Shader* shader;


public:
	Fog() {
		shader = ShaderManager::instance()->getShader("lightShader");
	
	}
	virtual ~Fog() {}

	void on();
	void off();
};