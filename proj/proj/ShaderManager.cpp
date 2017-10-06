#include "ShaderManager.h"
using namespace std;

ShaderManager* ShaderManager::instance = nullptr;

void ShaderManager::AddShader(const string& name, Shader* shader) {
	map.insert(make_pair(name, shader));
}

Shader* ShaderManager::GetShader(const string& name) {
	return map[name];
}

ShaderManager* ShaderManager::Instance() {
	if (instance == nullptr)
		instance = new ShaderManager;
	return instance;
}

void ShaderManager::Destroy() {
	for (auto element : map) {
		delete(element.second);
	}
	delete(instance);
}



