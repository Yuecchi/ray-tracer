#include "raytracer.h"

void Ray::setPosition(glm::vec3 pos) { Origin = pos; }
void Ray::setDirection(glm::vec3 dir) { Direction = dir; }
void Ray::setDistance(float d) { Distance = d; }