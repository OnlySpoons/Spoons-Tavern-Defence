#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include"Camera.h"

class Input
{
public:
	//Variables
	static Camera *camera;
	static float lastX;
	static float lastY;
	static bool firstMouse;

	//functions
	static void init(Camera *cam, unsigned int width, unsigned int height);

	static void checkInit();

	static void processInput(GLFWwindow* window, float deltaTime);

	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};

