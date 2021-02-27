#include "Window.h"

namespace Spoonity {

	//Constructor
	Window::Window(WindowProps properties)
		: _properties(properties)
	{
		//GLFW: initialise and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		_instance = glfwCreateWindow(_properties.width, _properties.height, _properties.title.c_str(), NULL, NULL);

		if (_instance == NULL)
		{
			glfwTerminate();
			throw "Failed to create GLFW window";
		}

		glfwMakeContextCurrent(_instance);
		glfwSetFramebufferSizeCallback(_instance, Input::framebufferSizeCallback);
		glfwSetScrollCallback(_instance, Input::scrollCallback);

		//Tell GLFW to capture mouse
		glfwSetInputMode(_instance, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		//Glad: load all OpenGL function pointers
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			throw "Failed to initialize GLAD";
		}
	}

	Window::~Window()
	{
		glfwTerminate();
	}

	//Function to get instance
	GLFWwindow* Window::getInstance() const
	{
		return _instance;
	}

	//Function to get width
	unsigned int Window::getWidth() const
	{
		return _properties.width;
	}

	//Function to get height
	unsigned int Window::getHeight() const
	{
		return _properties.height;
	}
	void Window::close() const
	{
		glfwSetWindowShouldClose(_instance, true);
	}
}