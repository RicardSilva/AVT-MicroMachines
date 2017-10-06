#include "MeshManager.h"

using namespace std;

MeshManager* MeshManager::instance = nullptr;

void MeshManager::AddMesh(const string& name, Mesh* mesh) {
	map.insert(make_pair(name, mesh));
}

Mesh* MeshManager::GetMesh(const string& name) {
	return map[name];
}

MeshManager* MeshManager::Instance() {
	if (instance == nullptr)
		instance = new MeshManager;
	return instance;
}

void MeshManager::Destroy() {
	for (auto element : map) {
		delete(element.second);
	}
	delete(instance);
}
