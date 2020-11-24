#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Camera.h"

#include <iostream>

class Window {
public:
	GLFWwindow* instance;
private:
	static unsigned int SCR_WIDTH;
	static unsigned int SCR_HEIGHT;

	// camera
	static Camera camera;
	static float lastX;
	static float lastY;
	static bool firstMouse;


public:
	Window();

	bool Create(const char* name);

	void processInput(GLFWwindow* window, float deltaTime);


	// Static functions

	static void framebuffer_size_callback(GLFWwindow *window, int width, int height);

	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

};