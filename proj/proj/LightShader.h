#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include <map>
#include <string>
#include "AVTmathLib.h"

#define VERTICES 0
#define NORMALS 1
#define TEXCOORDS 2

// The storage for matrices
extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

// The normal matrix
extern float mNormal3x3[9];

class LightShader : public Shader {

private:
	GLint projViewModelID;
	GLint viewModelID;
	GLint normalID;
	GLint lightPosID;
	GLint matAmbientID;
	GLint matDiffuseID;
	GLint matSpecularID;
	GLint matShininessID;

	GLint lightDirectionID;
	GLint lightColorID;


public:
	LightShader(const std::string& vertexShader, const std::string& fragmentShader) : Shader(vertexShader, fragmentShader) {
		bindAttributes();
		getUniformLocations();
	}
	virtual ~LightShader() {}

	void bindAttributes(void) {
		bindAttribute(VERTICES, "position");
		bindAttribute(NORMALS, "normal");
		bindAttribute(TEXCOORDS, "texCoord");
	}


	void getUniformLocations(void) {
		projViewModelID = getUniformLocation("m_pvm");
		viewModelID = getUniformLocation("m_viewModel");
		normalID = getUniformLocation("m_normal");
		lightPosID = getUniformLocation("l_pos");
		matAmbientID = getUniformLocation("mat.ambient");
		matDiffuseID = getUniformLocation("mat.diffuse");
		matSpecularID = getUniformLocation("mat.specular");
		matShininessID = getUniformLocation("mat.shininess");
		lightDirectionID = getUniformLocation("light.direction");
		lightColorID = getUniformLocation("light.color");
	}

	void loadProjViewModelMatrix(float* matrix) {
		Shader::loadMat4(projViewModelID, matrix);
	}
	void loadViewModelMatrix(float* matrix) {
		Shader::loadMat4(viewModelID, matrix);
	}
	void loadNormalMatrix(float* matrix) {
		Shader::loadMat3(normalID, matrix);
	}
	void loadLightPosition(vec3& vec) {
		Shader::loadVec3(normalID, vec);
	}
	void loadMaterial(Material& material) {
		Shader::loadVec3(matAmbientID, material.Ka);
		Shader::loadVec3(matDiffuseID, material.Kd);
		Shader::loadVec3(matSpecularID, material.Ks);
		Shader::loadFloat(matShininessID, material.Ns);
	}
	void loadDirectionalLight(DirectionalLight& light) {
		vec4 lightDir4 = multMatrixPoint(VIEW, vec4(light.direction, 0));
		vec3 lightDir = vec3(lightDir4.x, lightDir4.y, lightDir4.z);
		Shader::loadVec3(lightDirectionID, lightDir);
		Shader::loadVec3(lightColorID, light.color);
	}

	void loadMatrices() {
		computeDerivedMatrix(PROJ_VIEW_MODEL);
		loadViewModelMatrix(mCompMatrix[VIEW_MODEL]);
		loadProjViewModelMatrix(mCompMatrix[PROJ_VIEW_MODEL]);
		computeNormalMatrix3x3();
		loadNormalMatrix(mNormal3x3);
	}



};



