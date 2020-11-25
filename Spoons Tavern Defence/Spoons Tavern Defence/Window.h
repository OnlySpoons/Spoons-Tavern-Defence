#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input.h"

//A wrapper class for the GLFWwindow creation and manipulation
class Window {

//Member variables
public:
	GLFWwindow *instance; //The GLFWwindow instance

	//Variables for the screen width and height, set on construction
	unsigned int width;
	unsigned int height;

//Functions
public:

	//Constructor
	Window(unsigned int w, unsigned int h, const char *name);
};