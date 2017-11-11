#pragma once
#include "AVTmathLib.h"
#include "vec3.h"
#include "vec2.h"

extern float mCompMatrix[COUNT_COMPUTED_MATRICES][16];

class Camera {
protected:

	vec3 eye;
	vec3 target;
	vec3 up;
	float nearp, farp;

public:

	Camera(float nearp, float farp) : nearp(nearp), farp(farp) {}

	virtual ~Camera() {}

	void setEye(vec3& v) {
		eye = v;
	}
	vec3 getEye() {
		return eye;
	}
	void setTarget(vec3& v) {
		target = v;
	}
	vec3 getTarget() { return target;}
	void setUp(vec3& v) {
		up = v;
	}
	void computeView();
	virtual void computeProjection(int w, int h) {}
	void computeCarCameraPosition(const vec3& pos, int angle);
	void computeCockpitCameraPosition(const vec3& pos, int angle);
	void computeBackCameraPosition(const vec3& pos, int angle);
	
	static vec2 convertWorldToScreenSpace(vec3 worldPosition);
	
};

