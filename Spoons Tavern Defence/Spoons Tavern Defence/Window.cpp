#include "Window.h"

namespace spty {

	Window::Window(WindowProps properties)
		: properties_(properties)
	{
		//GLFW: initialise and configure
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		instance_ = glfwCreateWindow(properties_.width, properties_.height, properties_.title.c_str(), NULL, NULL);

		if (instance_ == NULL)
		{
			glfwTerminate();
			throw "Failed to create GLFW window";
		}

		glfwMakeContextCurrent(instance_);
		glfwSetFramebufferSizeCallback(instance_, Input::framebufferSizeCallback);
		glfwSetScrollCallback(instance_, Input::scrollCallback);

		//Tell GLFW to capture mouse
		glfwSetInputMode(instance_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

	GLFWwindow* Window::getInstance() const
	{
		return instance_;
	}

	unsigned int Window::getWidth() const
	{
		return properties_.width;
	}

	unsigned int Window::getHeight() const
	{
		return properties_.height;
	}

	void Window::close() const
	{
		glfwSetWindowShouldClose(instance_, true);
	}
}