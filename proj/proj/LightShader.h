#pragma once
#include <GL/glew.h>
#include "Shader.h"
#include <map>
#include <string>
#include "ObjLoader.h"

#define VERTICES 0
#define TEXCOORDS 1
#define NORMALS 2


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


public:
	LightShader(const std::string& vertexShader, const std::string& fragmentShader) : Shader(vertexShader, fragmentShader) {
		BindAttributes();
		GetUniformLocations();
	}
	virtual ~LightShader() {}

	void BindAttributes(void) {
		BindAttribute(VERTICES, "position");
		BindAttribute(TEXCOORDS, "texCoord");
		BindAttribute(NORMALS, "normal");
	}


	void GetUniformLocations(void) {
		projViewModelID = GetUniformLocation("m_pvm");
		viewModelID = GetUniformLocation("m_viewModel");
		normalID = GetUniformLocation("m_normal");
		lightPosID = GetUniformLocation("l_pos");
		matAmbientID = GetUniformLocation("mat.ambient");
		matDiffuseID = GetUniformLocation("mat.diffuse");
		matSpecularID = GetUniformLocation("mat.specular");
		matShininessID = GetUniformLocation("mat.shininess");
	}

	void LoadProjViewModelMatrix(float* matrix) {
		Shader::LoadMat4(projViewModelID, matrix);
	}
	void LoadViewModelMatrix(float* matrix) {
		Shader::LoadMat4(viewModelID, matrix);
	}
	void LoadNormalMatrix(float* matrix) {
		Shader::LoadMat3(normalID, matrix);
	}
	void LoadNormalMatrix(float* matrix) {
		Shader::LoadMat3(normalID, matrix);
	}
	void LoadLightPosition(vec3& vec) {
		Shader::LoadVec3(normalID, vec);
	}
	void LoadMaterial(objl::Material material) {
		Shader::LoadVec3(matAmbientID, material.Ka);
		Shader::LoadVec3(matDiffuseID, material.Kd);
		Shader::LoadVec3(matSpecularID, material.Ks);
		Shader::LoadFloat(matShininessID, material.Ns);
	}



};



