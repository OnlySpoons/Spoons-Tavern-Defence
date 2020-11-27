#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Input.h"

struct WindowProps
{
	std::string Title;
	unsigned int Width;
	unsigned int Height;

	WindowProps(const std::string& title = "Window", unsigned int width = 1280, unsigned int height = 720)
		: Title(title), Width(width), Height(height)
	{
	}
};

//A wrapper class for the GLFWwindow creation and manipulation
class Window
{

//Member variables
public:
	GLFWwindow *_Instance; //The GLFWwindow instance

	//Variables for the screen width and height, set on construction
	unsigned int _Width;
	unsigned int _Height;

//Functions
public:

	//Constructor
	Window(WindowProps properties);

	//TODO: add getWidth & getHeight
};