#ifndef DRAW_H
#define DRAW_H

#include <list>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#include "camera.h"
#include "primitives.h"
#include "raytracer.h"


struct PrimeRayManifold {
	Ray ray;
	Primitive *primitive;
};

PrimeRayManifold PrimeRayIntersectData(Ray, Primitive*);

void DrawPixel(glm::vec2, glm::vec3);

void DrawScene(Camera, unsigned int, unsigned int);

#endif

//maybe rename this header to raytracer
