#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include <map>
#include <string>
#include "AVTmathLib.h"

#define VERTICES 0
#define NORMALS 1
#define TEXCOORDS 2

#define MAX_LIGHTS 9

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

	GLint lightTypeID;
	GLint lightPositionID;
	GLint lightDirectionID;
	GLint lightColorID;
	GLint lightIntensityID;
	GLint lightConstAttenuationID;
	GLint lightLinAttenuationID;
	GLint lightQuadAttenuationID;


	GLint matAmbientID;
	GLint matDiffuseID;
	GLint matSpecularID;
	GLint matShininessID;

	int lightCounter;
	GLuint lightsUboHandle;
	GLuint lightsUboID;
	GLubyte* lightsBlockBuffer;
	GLint lightsBlockSize;
	GLuint lightsIndices[8];
	GLint lightsOffsets[8];
	GLchar* lightsNames[8] = { "type", "position", "direction", "color", "intensity", 
		"constantAttenuation", "linearAttenuation", "quadraticAttenuation" };



public:
	LightShader(const std::string& vertexShader, const std::string& fragmentShader) : Shader(vertexShader, fragmentShader) {
		lightCounter = 0;
		bindAttributes();
		getUniformLocations();
		initializeLightsUbo();
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

		lightTypeID = getUniformLocation("light.type");
		lightPositionID = getUniformLocation("light.position");
		lightDirectionID = getUniformLocation("light.direction");
		lightColorID = getUniformLocation("light.color");
		lightIntensityID = getUniformLocation("light.intensity");
		lightConstAttenuationID = getUniformLocation("light.constantAttenuation");
		lightLinAttenuationID = getUniformLocation("light.linearAttenuation");
		lightQuadAttenuationID = getUniformLocation("light.quadraticAttenuation");
	}


	void initializeLightsUbo() {
		lightsUboHandle = 0;
		lightsUboID = getUniformBlockIndex("lightsBuffer");
		glGetActiveUniformBlockiv(program, lightsUboID,
			GL_UNIFORM_BLOCK_DATA_SIZE, &lightsBlockSize);
		lightsBlockBuffer = (GLubyte*)malloc(lightsBlockSize * MAX_LIGHTS);

		glGetUniformIndices(program, 8, lightsNames, lightsIndices);
		glGetActiveUniformsiv(program, 8, lightsIndices, GL_UNIFORM_OFFSET, lightsOffsets);

		glGenBuffers(1, &lightsUboHandle);
		glBindBuffer(GL_UNIFORM_BUFFER, lightsUboHandle);

		glBufferData(GL_UNIFORM_BUFFER, lightsBlockSize * MAX_LIGHTS, lightsBlockBuffer, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, lightsUboID, lightsUboHandle);

	}
	void deleteLightsUbo() {
		delete(lightsBlockBuffer);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
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
		vec4 lightDir4 = multMatrixPoint(VIEW, light.direction);
		vec3 lightDir = vec3(lightDir4.x, lightDir4.y, lightDir4.z);
		Shader::loadInt(lightTypeID, light.type);
		Shader::loadVec3(lightDirectionID, lightDir);
		Shader::loadVec3(lightColorID, light.color);
	}
	void loadPointLight(PointLight& light) {
		vec4 lightPos4 = multMatrixPoint(VIEW, light.position);
		vec3 lightPos = vec3(lightPos4.x, lightPos4.y, lightPos4.z);
		Shader::loadInt(lightTypeID, light.type);
		Shader::loadVec3(lightPositionID, lightPos);
		Shader::loadVec3(lightColorID, light.color);

		Shader::loadFloat(lightConstAttenuationID, light.constantAttenuation);
		Shader::loadFloat(lightLinAttenuationID, light.linearAttenuation);
		Shader::loadFloat(lightQuadAttenuationID, light.quadraticAttenuation);
	}

	void loadMatrices() {
		computeDerivedMatrix(PROJ_VIEW_MODEL);
		loadViewModelMatrix(mCompMatrix[VIEW_MODEL]);
		loadProjViewModelMatrix(mCompMatrix[PROJ_VIEW_MODEL]);
		computeNormalMatrix3x3();
		loadNormalMatrix(mNormal3x3);
	}



};



