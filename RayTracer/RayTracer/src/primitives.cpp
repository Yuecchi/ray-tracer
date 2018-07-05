#include "primitives.h"

bool IsEven(int value) {
	return !(value % 2);
}

/*Primitives*/

/*Planes*/
void Plane::setNormal(glm::vec3 N) {
	Normal = normalize(N);
	Origin = (Normal * Distance);
}

void Plane::setDistance(float D) {
	Distance = D;
	Origin = (Normal * Distance);
}

float Plane::RayIntersect(Ray ray) {
	float denom = dot(ray.direction(), Normal);
	if (fabs(denom) > 1e-6) {
		glm::vec3 w = Origin - ray.origin();
		float numer = dot(w, Normal);
		float t = numer / denom;
		if (t >= 1e-6) {
			return t;
		}
		else return INFINITY;
	}
	return INFINITY;
}

glm::vec3 Plane::GetColor(glm::vec3 p) {
	
	glm::vec3 Color;

	switch (texture) {
		case tx_none:
			Color = color;
			break;
		case tx_chequered: {
			//set tile size
			static const int d = 5;
			//project point 'p' onto the plane v and u vectors
			glm::vec3 PtoV, PtoU;
			PtoV = v() * dot(p, v());
			PtoU = u() * dot(p, u());
			//calculate distance from origin to projections
			int dv = (int)glm::distance(origin(), origin() + PtoV);
			int du = (int)glm::distance(origin(), origin() + PtoU);
			//divive the distance by the size of the tiles
			int OddEvenV = (int)(dv / d);
			int OddEvenU = (int)(du / d);
			if (p.x >= 0) {
				if (IsEven(OddEvenV) && IsEven(OddEvenU)) Color = glm::vec3(0, 0, 0);
				else if (!IsEven(OddEvenV) && !IsEven(OddEvenU)) Color = glm::vec3(0, 0, 0);
				else Color = glm::vec3(1, 1, 1);
			}
			else {
				if (IsEven(OddEvenV) && IsEven(OddEvenU)) Color = glm::vec3(1, 1, 1);
				else if (!IsEven(OddEvenV) && !IsEven(OddEvenU)) Color = glm::vec3(1, 1, 1);
				else Color = glm::vec3(0, 0, 0);
			}
			return Color;
			break;
		}
		default: 
			Color = color;
			break;
	}

	return Color;
}

/*Spheres*/

void Sphere::setPosition(glm::vec3 pos) {
	center = pos;
}

float Sphere::RayIntersect(Ray ray) {
	glm::vec3 w = ray.origin() - center;

	float a = dot(ray.direction(), ray.direction());
	float b = dot(ray.direction(), w);
	float c = dot(w, w) - (radius * radius);

	float discr = (b * b) - (a * c);
	if (discr < 0) return INFINITY; //no intersection

	float t = (-b - sqrt(discr)) / a;
	return t;
	//if (t >= 1e-6) return t;
	//else return INFINITY;
}

glm::vec3 Sphere::GetColor(glm::vec3 p) {

	glm::vec3 Color;

	switch (texture) {
	case tx_none:
		Color = color;
		break;
	case tx_chequered:
		Color = color;
		break;
	default:
		Color = color;
		break;
	}

	return Color;
}

/*Triangles*/