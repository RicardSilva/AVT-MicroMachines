#pragma once
#include "Mesh.h"
#include <map>

using namespace std;

class MeshManager {

private:
	static MeshManager* instance;
	map<string, Mesh*> map;
	MeshManager() {};


public:

	void AddMesh(const string& name, Mesh* mesh);
	Mesh *GetMesh(const string& name);

	static MeshManager* Instance();
	void Destroy();

};
