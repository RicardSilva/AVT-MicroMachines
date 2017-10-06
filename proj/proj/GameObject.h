#pragma once
#include "vec3.h"
#include "Shader.h"
#include "ObjLoader.h"
#include "AVTmathLib.h"

class GameObject {

	
	objl::Loader* Loader;
	

protected:
	Shader* shader;
	std::vector<objl::Mesh*> meshes;
	vec3 position;

public:
	GameObject(vec3& position, Shader* shader, std::string& obj) : position(position), shader(shader) {
		Loader = new objl::Loader();
		if (obj.compare(std::string("")) != 0) {
			Loader->LoadFile(obj);
			meshes = Loader->LoadedMeshes;
			delete Loader;
		}
	}
	virtual ~GameObject() {}

	vec3 getPosition() { return position; }

	virtual void draw();
	virtual void update(float timeStep) = 0;

};