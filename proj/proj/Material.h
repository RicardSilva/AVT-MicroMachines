#pragma once
struct Material{
	float diffuse[4];	//Kd
	float ambient[4];	//Ka
	float specular[4];	//Ks
	float emissive[4];	//Ke
	float shininess;	//Ns
	int texCount;
};