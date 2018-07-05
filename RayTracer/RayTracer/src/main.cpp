#include <iostream>

#include <GLEW/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

#include "draw.h"
#include "camera.h"
#include "primitives.h"
#include "raytracer.h"

//Create prototype function for windowsize callback
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

//Set values for initial window size
const unsigned int ScreenWidth = 500;
const unsigned int ScreenHeight = 500;

Camera camera; //creates a camera at the origin with the default directions

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit()) {
		std::cout << "Error Initializing  GLFW\n";
		return -1;
	}
	else {
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(ScreenWidth, ScreenHeight, "RayTracer", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//Set the viewport to be the entire size of the window
	glViewport(0, 0, ScreenWidth, ScreenHeight);

	//Change to the projection matrix, reset the matrix and set up orthagonal projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Setup orthgraphic projection
	glOrtho(0, ScreenWidth, ScreenHeight, 0, 0, 1);

	// OpenGL Settings
	glfwSwapInterval(1); //lock vertical sync of monitor(60hz)

						 //Set the window and function to manage the window size callback event
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	/*Initialize GLEW*/
	if (glewInit() != GLEW_OK) {
		std::cout << "Error Initializing  GLEW\n";
	}
	else {
		std::cout << glGetString(GL_VERSION) << "\n";
	}

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		/*Draw the scene*/
		DrawScene(camera, ScreenWidth, ScreenHeight);

		//camera.pan(0.1);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	/*Change the viewport when the window size is changed*/
	glViewport(0, 0, width, height);
}