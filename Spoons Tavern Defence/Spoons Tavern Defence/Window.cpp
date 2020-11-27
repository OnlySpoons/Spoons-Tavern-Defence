#include "Window.h"

//Constructor
Window::Window(WindowProps properties)
	: _Width(properties.Width), _Height(properties.Height)
{
	//GLFW: initialise and configure
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	_Instance = glfwCreateWindow(_Width, _Height, properties.Title.c_str(), NULL, NULL);

	if (_Instance == NULL)
	{
		glfwTerminate();
		throw "Failed to create GLFW window";
	}

	glfwMakeContextCurrent(_Instance);
	glfwSetFramebufferSizeCallback(_Instance, Input::framebufferSizeCallback);
	glfwSetCursorPosCallback(_Instance, Input::mouseCallback);
	glfwSetScrollCallback(_Instance, Input::scrollCallback);

	//Tell GLFW to capture mouse
	glfwSetInputMode(_Instance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}