#pragma once

#include <map>
#include "vec3.h"
#include "vec4.h"
#include <string>
#include "ObjLoader.h"
#include <GL/glew.h>


struct DirectionalLight;

using namespace std;
class Shader
{


public:
	Shader(const std::string& vertexShader, const std::string& fragmentShader) {
		totalShaders = 0;
		shaders[VERTEX_SHADER] = 0;
		shaders[FRAGMENT_SHADER] = 0;

		loadFromFile(GL_VERTEX_SHADER, vertexShader);
		loadFromFile(GL_FRAGMENT_SHADER, fragmentShader);
		createProgram();
		linkProgram();
	}
	virtual ~Shader(void) {
		deleteProgram();
	}
	void loadFromString(GLenum whichShader, const std::string& source);
	void loadFromFile(GLenum whichShader, const std::string& filename);
	GLuint createProgram();
	void linkProgram();

	GLuint getProgram() const {
		return program;
	}

	void use();
	void unUse();

	virtual void bindAttributes(void) = 0;
	virtual void getUniformLocations(void) = 0;

	virtual void loadProjViewModelMatrix(float* matrix) {}
	virtual void loadViewModelMatrix(float* matrix) {}
	virtual void loadNormalMatrix(float* matrix) {}
	virtual void loadLightPosition(vec3& vec) {}
	virtual void loadDirectionalLight(DirectionalLight& light) {}
	virtual void loadMaterial(Material& material) {}
	virtual void loadMatrices() {}

	void loadInt(GLint location, GLint i);
	void loadFloat(GLint location, GLfloat f);
	void loadVec3(GLint location, vec3 &v);
	void loadVec4(GLint location, vec4 &v);
	void loadMat3(GLint location, float* m);
	void loadMat4(GLint location, float* m);
	//void LoadTexture(GLint location, Texture *t);


	void bindAttribute(GLint attribute, const GLchar* variableName);
	GLint getUniformLocation(const GLchar* source);
	//void BindUniformBlock(GLuint uniformBlockIndex, GLuint uniformBlockBinding);
	GLint getUniformBlockIndex(const GLchar* source);


	void deleteProgram();

private:
	enum ShaderType { VERTEX_SHADER, FRAGMENT_SHADER };
	int totalShaders;
	GLuint shaders[2];//0->vertexshader, 1->fragmentshaders
protected:
	GLuint	program;
};

