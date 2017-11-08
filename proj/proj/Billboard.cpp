#include "Billboard.h"

void Billboard::draw(vec3 cam) {
	float pos[3] = { position.x , position.y, position.z };
	float camPos[3] = { cam.x , cam.y, cam.z };

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	pushMatrix(MODEL);
	translate(MODEL, position);

	l3dBillboardCylindricalBegin(camPos, pos);

	shader->loadMatrices();

	shader->enableTextures();
	shader->loadTextureMode(1);

	glActiveTexture(GL_TEXTURE10);
	glBindTexture(GL_TEXTURE_2D, TextureArray[0]);

	shader->loadTree(10);

	for (auto mesh : model->meshes) {
		shader->loadMaterial(mesh->MeshMaterial);
		mesh->draw();
	}

	shader->disableTextures();
	glBindTexture(GL_TEXTURE_2D, 0);


	popMatrix(MODEL);
}

#define mathsInnerProduct(v,q) \
	((v)[0] * (q)[0] + \
	(v)[1] * (q)[1] + \
	(v)[2] * (q)[2])	

#define mathsCrossProduct(a,b,c) \
	(a)[0] = (b)[1] * (c)[2] - (c)[1] * (b)[2]; \
	(a)[1] = (b)[2] * (c)[0] - (c)[2] * (b)[0]; \
	(a)[2] = (b)[0] * (c)[1] - (c)[0] * (b)[1];


inline void mathsNormalize(float *v) {
	float d = (sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2])));
	v[0] = v[0] / d;
	v[1] = v[1] / d;
	v[2] = v[2] / d;
}

void Billboard::l3dBillboardCylindricalBegin(float *cam, float *worldPos) {

	float lookAt[3] = { 0,0,1 }, objToCamProj[3], upAux[3], angleCosine;

	// objToCamProj is the vector in world coordinates from the local origin to the camera
	// projected in the XZ plane
	objToCamProj[0] = cam[0] - worldPos[0];
	objToCamProj[1] = 0;
	objToCamProj[2] = cam[2] - worldPos[2];


	// normalize both vectors to get the cosine directly afterwards
	mathsNormalize(objToCamProj);

	// easy fix to determine wether the angle is negative or positive
	// for positive angles upAux will be a vector pointing in the 
	// positive y direction, otherwise upAux will point downwards
	// effectively reversing the rotation.
	mathsCrossProduct(upAux, lookAt, objToCamProj);

	// compute the angle
	angleCosine = mathsInnerProduct(lookAt, objToCamProj);

	// perform the rotation. The if statement is used for stability reasons
	// if the lookAt and v vectors are too close together then |aux| could
	// be bigger than 1 due to lack of precision
	if ((angleCosine < 0.99990) && (angleCosine > -0.9999))
		rotate(MODEL, acos(angleCosine) * 180 / 3.14, upAux[0], upAux[1], upAux[2]);
}