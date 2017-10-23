#include "Border.h"

Border::Border(vec3 position, float width, float length) : width(width), length(length),
GameObject(position, new Hitbox(vec3(position.x - width, 0, position.z - length),
								vec3(position.x + width, 20, position.z + length))) {}