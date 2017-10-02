#pragma once
#include "vec3.h"
#include "Mesh.h"
#include "AVTmathLib.h"
#include "Material.h"
class Track {

	Mesh* mesh;
	Material material;
	vec3 position;


public:
	Track() {
		position = vec3(0.0f, 0.0f, 0.0f);
		mesh = new Mesh(std::string("objs/cube.obj"));
	}
	virtual ~Track() {}

	void update(float timeStep);
	void draw();


};