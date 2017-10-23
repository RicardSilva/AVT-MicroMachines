#include "Hitbox.h"

bool Hitbox::hasCollision(Hitbox *h) {
	bool t = ((getXmax() > h->getXmin()) && (getXmin() < h->getXmax()) && (getZmax() > h->getZmin()) && (getZmin() < h->getZmax()));
	return t;
}

void Hitbox::set(float xmin, float ymin, float zmin, float xmax, float ymax, float zmax) {
	minCorner = vec3(xmin, ymin, zmin);
	maxCorner = vec3(xmax, ymax, zmax);
	center = vec3(xmin + (xmax - xmin) / 2.0f, ymin + (ymax - ymin) / 2.0f, zmin + (zmax - zmin) / 2.0f);

}


void Hitbox::draw() {

	if (DEBUG_ACTIVE) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		pushMatrix(MODEL);

		translate(MODEL, getXmax() - (getXmax() - getXmin()) / 2,
			getYmax() - (getYmax() - getYmin()) / 2,
			getZmax() - (getZmax() - getZmin()) / 2);

		scale(MODEL, getXmax() - getXmin(), getYmax() - getYmin(), getZmax() - getZmin());
		shader->loadMatrices();

		for (auto mesh : model->meshes) {
			shader->loadMaterial(mesh->MeshMaterial);
			mesh->draw();
		}
		popMatrix(MODEL);

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}

}