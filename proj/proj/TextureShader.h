#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include <map>
#include <string>
#include "AVTmathLib.h"
#include <sstream>
#include "Light.h"

#define VERTICES 0
#define NORMALS 1
#define TEXCOORDS 2


// The storage for matrices
extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

// The normal matrix
extern float mNormal3x3[9];

class TextureShader : public Shader {

private:
	GLint projViewModelID;
	GLint viewModelID;
	GLint textureID;
	GLint modeID;
	GLint matDiffuseID;
public:
	TextureShader(const std::string& vertexShader, const std::string& fragmentShader) : Shader(vertexShader, fragmentShader) {
		bindAttributes();
		getUniformLocations();
	}
	virtual ~TextureShader() {
	}

	void bindAttributes(void) {
		bindAttribute(VERTICES, "position");
		bindAttribute(NORMALS, "normal");
		bindAttribute(TEXCOORDS, "texCoord");
	}
	void getUniformLocations(void) {
		projViewModelID = getUniformLocation("m_pvm");
		viewModelID = getUniformLocation("m_viewModel");

		textureID = getUniformLocation("textureMap");
		modeID = getUniformLocation("mode");
		matDiffuseID = getUniformLocation("matDiffuse");
	}

	void loadProjViewModelMatrix(float* matrix) {
		Shader::loadMat4(projViewModelID, matrix);
	}
	void loadViewModelMatrix(float* matrix) {
		Shader::loadMat4(viewModelID, matrix);
	}
	
	void loadTexture(GLint id) {
		Shader::loadInt(textureID, id);
	}
	void loadTextureMode(GLint mode) {
		Shader::loadInt(modeID, mode);
	}
	void loadMatDiffuse(vec4& color) {
		Shader::loadVec4(matDiffuseID, color);
	}
	void loadMatrices() {
		computeDerivedMatrix(PROJ_VIEW_MODEL);
		loadViewModelMatrix(mCompMatrix[VIEW_MODEL]);
		loadProjViewModelMatrix(mCompMatrix[PROJ_VIEW_MODEL]);
	}


};



