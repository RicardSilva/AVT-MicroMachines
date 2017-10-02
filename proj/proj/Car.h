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
		position = vec3(0.0f, 5.0f,0.0f);
		mesh = new Mesh(std::string("objs/car2.obj"));
	}
	virtual ~Car() {}
	vec3 getPosition() { return position; }
	void update(float timeStep);
	void draw();


};