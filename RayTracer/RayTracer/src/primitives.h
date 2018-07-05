#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <string>
#include <list>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "raytracer.h"

class Primitive {
	protected: //protected structures
	enum Texture {		
		tx_none,
		tx_chequered
	};
	protected: //protected members
		std::string Type;
	public: //public members
		Texture texture;
		glm::vec3 color;
	public: //referencing
		std::string type() { return Type; }
	public: //object list
		static std::list<Primitive*> SceneObjects;
	public: //virtual functions
		virtual float RayIntersect(Ray) = 0;
		virtual glm::vec3 GetColor(glm::vec3) = 0;
};

class Plane : public Primitive {
	private: //members
		glm::vec3 Normal;
		float Distance;
		glm::vec3 Origin;
		glm::vec3 V, U;
	public: //constructors
		Plane() : Normal(glm::vec3(0, 1, 0)), Distance(0) {
			Type = "plane";			
			Origin = (Normal * Distance);
			V = glm::vec3(0, 0, 1);
			U = glm::vec3(1, 0, 0);
			color = glm::vec3(1, 1, 1);
			texture = tx_chequered;
			SceneObjects.push_back(this);
		}
		Plane(glm::vec3 N, float D) : Normal(N), Distance(D) {
			Type = "plane";
			Normal = normalize(Normal);
			Origin = (Normal * Distance);
			V = glm::vec3(Normal.x, -Normal.z, Normal.y);
			U = cross(Normal, V);
			color = glm::vec3(1, 1, 1);
			texture = tx_chequered;
			SceneObjects.push_back(this);
		}
	public: //referencing
		glm::vec3 normal() { return Normal; }
		float distance() { return Distance; }
		glm::vec3 origin() { return Origin; }
		glm::vec3 v() { return V; }
		glm::vec3 u() { return U; }
	public: //assignment
		void setNormal(glm::vec3);
		void setDistance(float);
	public: //methods
		float RayIntersect(Ray);
		glm::vec3 GetColor(glm::vec3);
};

class Sphere : public Primitive {
	public: //members
		glm::vec3 center;
		float radius;
	public: //constructors
		Sphere() : center(glm::vec3(0, 0, 0)), radius(0) {
			Type = "sphere";
			color = glm::vec3(0, 1, 0); //green
			texture = tx_none;
			SceneObjects.push_back(this);
		}
		Sphere(glm::vec3 C, float R) : center(C), radius(R) {
			Type = "sphere"; 
			color = glm::vec3(0, 1, 0); //green
			texture = tx_none;
			SceneObjects.push_back(this);
		}
	public: //assignment
		void setPosition(glm::vec3);
	public: //methods
		float RayIntersect(Ray);
		glm::vec3 GetColor(glm::vec3);
};

#endif  PRIMITIVES_H

//notes: 
//change default colour of spheres back to white
//change default texture of planes back to tx_none
//figure out a good place to change these values
