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

#define MAX_LIGHTS 9
#define ATTRIBS_PER_LIGHT 11

// The storage for matrices
extern float mMatrix[COUNT_MATRICES][16];
extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

// The normal matrix
extern float mNormal3x3[9];

class LightShader : public Shader {

private:

	int activeLightsCounter = MAX_LIGHTS;
	GLint projViewModelID;
	GLint viewModelID;
	GLint normalID;
	GLint lightPosID;
	
	GLint matAmbientID;
	GLint matDiffuseID;
	GLint matSpecularID;
	GLint matShininessID;

	int lightCounter;
	GLint lightUniforms[MAX_LIGHTS][ATTRIBS_PER_LIGHT];
	GLchar* lightAttribNames[ATTRIBS_PER_LIGHT] = { "isActive", "type", "position", "direction",
		"color", "intensity", "constantAttenuation", "linearAttenuation", "quadraticAttenuation", "spotCosCutoff", "spotExponent" };


public:
	LightShader(const std::string& vertexShader, const std::string& fragmentShader) : Shader(vertexShader, fragmentShader) {
		lightCounter = 0;
		bindAttributes();
		getUniformLocations();
	}
	virtual ~LightShader() {
	}

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

		/*lightTypeID = getUniformLocation("light.type");
		lightPositionID = getUniformLocation("light.position");
		lightDirectionID = getUniformLocation("light.direction");
		lightColorID = getUniformLocation("light.color");
		lightIntensityID = getUniformLocation("light.intensity");
		lightConstAttenuationID = getUniformLocation("light.constantAttenuation");
		lightLinAttenuationID = getUniformLocation("light.linearAttenuation");
		lightQuadAttenuationID = getUniformLocation("light.quadraticAttenuation");*/
		

		std::string uniformName;
		for (int i = 0; i < MAX_LIGHTS; i++) {
			for (int j = 0; j < ATTRIBS_PER_LIGHT; j++) {
				uniformName = "lights[" + std::to_string(i) + "]." + lightAttribNames[j];
				lightUniforms[i][j] = getUniformLocation(uniformName.c_str());
			}
			

		}
	}

	void updateLightCounter() {
		lightCounter++;
		if (lightCounter >= MAX_LIGHTS )
			lightCounter = 0;
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
	void loadMaterial(Material& material) {
		Shader::loadVec3(matAmbientID, material.Ka);
		Shader::loadVec3(matDiffuseID, material.Kd);
		Shader::loadVec3(matSpecularID, material.Ks);
		Shader::loadFloat(matShininessID, material.Ns);		
	}
	void loadDirectionalLight(Light& light) {
		vec4 lightDir = multMatrixPoint(VIEW, light.direction);

		Shader::loadBool(lightUniforms[lightCounter][0], light.isActive);
		Shader::loadInt(lightUniforms[lightCounter][1], light.type);
		Shader::loadVec4(lightUniforms[lightCounter][3], lightDir);
		Shader::loadVec3(lightUniforms[lightCounter][4], light.color);
		Shader::loadFloat(lightUniforms[lightCounter][5], light.intensity);

		updateLightCounter();
	}
	void loadPointLight(Light& light) {
		vec4 lightPos = multMatrixPoint(VIEW, light.position);

		Shader::loadBool(lightUniforms[lightCounter][0], light.isActive);
		Shader::loadInt(lightUniforms[lightCounter][1], light.type);
		Shader::loadVec4(lightUniforms[lightCounter][2], lightPos);
		Shader::loadVec3(lightUniforms[lightCounter][4], light.color);
		Shader::loadFloat(lightUniforms[lightCounter][5], light.intensity);

		Shader::loadFloat(lightUniforms[lightCounter][6], light.constantAttenuation);
		Shader::loadFloat(lightUniforms[lightCounter][7], light.linearAttenuation);
		Shader::loadFloat(lightUniforms[lightCounter][8], light.quadraticAttenuation);


		updateLightCounter();
	}
	void loadSpotLight(Light& light) {
		vec4 lightPos = multMatrixPoint(VIEW, light.position);
		vec4 lightDir = multMatrixPoint(VIEW, light.direction);

		Shader::loadBool(lightUniforms[lightCounter][0], light.isActive);
		Shader::loadInt(lightUniforms[lightCounter][1], light.type);
		Shader::loadVec4(lightUniforms[lightCounter][2], lightPos);
		Shader::loadVec4(lightUniforms[lightCounter][3], lightDir);
		Shader::loadVec3(lightUniforms[lightCounter][4], light.color);
		Shader::loadFloat(lightUniforms[lightCounter][5], light.intensity);

		Shader::loadFloat(lightUniforms[lightCounter][6], light.constantAttenuation);
		Shader::loadFloat(lightUniforms[lightCounter][7], light.linearAttenuation);
		Shader::loadFloat(lightUniforms[lightCounter][8], light.quadraticAttenuation);

		Shader::loadFloat(lightUniforms[lightCounter][9], light.spotCosCutoff);
		Shader::loadFloat(lightUniforms[lightCounter][10], light.spotExponent);

		updateLightCounter();
	}

	void loadMatrices() {
		computeDerivedMatrix(PROJ_VIEW_MODEL);
		loadViewModelMatrix(mCompMatrix[VIEW_MODEL]);
		loadProjViewModelMatrix(mCompMatrix[PROJ_VIEW_MODEL]);
		computeNormalMatrix3x3();
		loadNormalMatrix(mNormal3x3);
	}

	void decActiveLights(){ activeLightsCounter--; }
	void incActiveLights(){ activeLightsCounter++; }

};



