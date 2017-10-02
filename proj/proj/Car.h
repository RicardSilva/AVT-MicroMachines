#pragma once
#include "vec3.h"
#include "Mesh.h"
#include "AVTmathLib.h"
#include "Material.h"
class Car {
	
	Mesh* mesh;
	Material material;
	vec3 position;
	float angle;
	

public:
	Car() {
		position = vec3(0.0f,0.0f,0.0f);
		mesh = new Mesh(std::string("objs/cube.obj"));
	}
	virtual ~Car() {}

	void update(float timeStep);
	void draw();


};