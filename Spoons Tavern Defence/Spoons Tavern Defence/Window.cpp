#include "Window.h"

//Constructor
Window::Window(unsigned int w, unsigned int h, const char* name)
	: width(w), height(h)
{
	// glfw: initialise and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	instance = glfwCreateWindow(width, height, name, NULL, NULL);

	if (instance == NULL)
	{
		glfwTerminate();
		throw "Failed to create GLFW window";
	}

	glfwMakeContextCurrent(instance);
	glfwSetFramebufferSizeCallback(instance, Input::framebuffer_size_callback);
	glfwSetCursorPosCallback(instance, Input::mouse_callback);
	glfwSetScrollCallback(instance, Input::scroll_callback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(instance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}