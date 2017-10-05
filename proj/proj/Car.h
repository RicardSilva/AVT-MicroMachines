#pragma once
#include "vec3.h"
#include "AVTmathLib.h"
#include "ObjLoader.h"

class Car {
	
	std::vector<objl::Mesh> meshes;
	vec3 position;
	float angle;
	
	objl::Loader* Loader;

public:
	Car() {
		position = vec3(0.0f, 5.0f,0.0f);
		Loader = new objl::Loader();
		Loader->LoadFile("objs/car2.obj");
		meshes = Loader->LoadedMeshes;
		//delete Loader;
	}
	virtual ~Car() {}
	vec3 getPosition() { return position; }
	void update(float timeStep);
	void draw();


};
