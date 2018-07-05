#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <glm\vec3.hpp>

//#include "primitives.h"

class Ray {
	public: //members
		glm::vec3 Origin;
		glm::vec3 Direction;
		float Distance;
	public: //constructors
		Ray() : Origin(glm::vec3(0, 0, 0)), Direction(glm::vec3(0, 0, 0)), Distance(INFINITY) {}
		Ray(glm::vec3 O, glm::vec3 D, float dis) : Origin(O), Direction(D), Distance(dis) {
		}
	public: //referencing
		glm::vec3 origin() { return Origin; }
		glm::vec3 direction() { return Direction; }
		float distance() { return Distance; }
	public: //assignment
		void setPosition(glm::vec3);
		void setDirection(glm::vec3);
		void setDistance(float);
};


#endif RAYTRACER_H	
