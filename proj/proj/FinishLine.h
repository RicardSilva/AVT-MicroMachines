#pragma once
#include "Border.h"
class FinishLine : public Border {

public:
	FinishLine(vec3 position, float width, float length) : Border(position, width, length) { }

};