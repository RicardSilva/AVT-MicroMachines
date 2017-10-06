#pragma once
#include "Shader.h"
#include <map>


class ShaderManager {

private:
	static ShaderManager* instance;
	map<string, Shader*> map;
	ShaderManager() {};


public:

	void AddShader(const string& name, Shader* shader);
	Shader* GetShader(const string& name);

	static ShaderManager* Instance();
	void Destroy();

};
