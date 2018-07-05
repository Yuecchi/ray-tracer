#include <GLFW/glfw3.h>

#include "draw.h"

std::list<Primitive*> Primitive::SceneObjects;

Plane plane(glm::vec3(0.0, 1.0, 0.0), -10.0); //plane for testing
Sphere sphere(glm::vec3(0.0, 0.0, -15.0), 5.0); // sphere for testing

void DrawPixel(glm::vec2 pos, glm::vec3 color) {
	glColor3f(color.r, color.g, color.b);

	glBegin(GL_POINTS);
	glVertex2f(pos.x, pos.y);
	glEnd();
}

PrimeRayManifold PrimeRayIntersectData(Ray ray, Primitive* primitive) {
	PrimeRayManifold manifold;
	manifold.ray = ray;
	manifold.primitive = primitive;
	return manifold;
}

void DrawScene(Camera camera, unsigned int width, unsigned int height) {
	static glm::vec3 CanvasCenter(0, 0, -1); //note:  will have to change this implementation after adding movement to the camera
	static glm::vec3 P[3]; //corners of the canvas
	PrimeRayManifold manifold;

	/*set corners of canvas (in the current state of the program I only actually have to set these once)*/
	P[1] = CanvasCenter - camera.rightVec() + camera.upVec(); //top left
	P[0] = CanvasCenter + camera.rightVec() + camera.upVec(); //top right
	P[2] = CanvasCenter + camera.rightVec() - camera.upVec(); //bottom right

	/*calculate the canvas' height and width*/
	glm::vec3 CanvasWidth = P[0] - P[1];
	glm::vec3 CanvasHeight = P[2] - P[0];

	for (int y = 0; y < height; y++) {
		/*create initial ray to be fired from the camera into the scene*/
		static Ray primeRay(camera.position(), camera.direction(), INFINITY);
		/*calculate ray's y direction*/
		float Py = P[1].y + (y * (CanvasHeight.y / (height - 1)));
		for (int x = 0; x < width; x++) {
			float Px = P[1].x + (x * (CanvasWidth.x / (width - 1)));
			primeRay.setDirection(glm::vec3(Px, Py, camera.direction_z()));
			float t = INFINITY;
			manifold.ray = primeRay;
			//check each object in the scene for intersctions with the current ray
			for each(Primitive* ScnObj in Primitive::SceneObjects) {
				float next_t = ScnObj->RayIntersect(primeRay); 
				if (next_t < t) { //evaluate lowest value of t
					t = next_t;
					manifold.ray.setDistance(t);
					manifold.primitive = ScnObj;
				}
			}

			if (t != INFINITY) {
				glm::vec3 CurrentColor;
				glm::vec3 I = primeRay.origin() + (primeRay.direction() * t);
				CurrentColor = manifold.primitive->GetColor(I);
				DrawPixel(glm::vec2(x, y), CurrentColor);
			}
			else DrawPixel(glm::vec2(x, y), glm::vec3(0, 0, 1));

		}
	}
}