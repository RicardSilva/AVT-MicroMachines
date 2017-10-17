#include "Border.h"

Border::Border(vec3 position, float width, float length) : _width(width), _length(length),
GameObject(position, new Hitbox(vec3(position.x - width / 2.0, position.y - length / 2.0, position.z),
								vec3(position.x + width / 2.0, position.y + length / 2.0, position.z + 50))) {}
