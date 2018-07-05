#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>

class Camera {
	private: //members
		glm::vec3 Position;
		glm::vec3 Direction;
		glm::vec3 UpVec;
		glm::vec3 RightVec;
	public: //constructors
		Camera() : Position(glm::vec3(0, 0, 0)), Direction(glm::vec3(0, 0, -1)), UpVec(glm::vec3(0, 1, 0)), RightVec(glm::vec3(-1, 0, 0)) {}
	public: //referencing
		glm::vec3 position() { return Position; }
		glm::vec3 direction() { return Direction; }
		glm::vec3 upVec() { return UpVec; }
		glm::vec3 rightVec() { return RightVec; }
		float direction_x() { return Direction.x; }
		float direction_y() { return Direction.y; }
		float direction_z() { return Direction.z; }
	public: //methods
		void pan(float s) { Position.x += s; }
};

#endif CAMERA_H