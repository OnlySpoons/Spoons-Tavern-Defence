#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>

#include "Input.h"

namespace spty {

	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProps(const std::string& title = "Window", unsigned int width = 1280, unsigned int height = 720)
			: title(title), width(width), height(height)
		{
		}
	};

	//A wrapper class for the GLFWwindow creation and manipulation
	class Window
	{

		//Member variables
	private:
		GLFWwindow* _instance; //The GLFWwindow instance

		WindowProps _properties; //Window Properties

	//Functions
	public:

		//Constructor
		Window(WindowProps properties);

		//Destructor
		~Window();

		//Function to get instance
		GLFWwindow* getInstance() const;

		//Function to get width
		unsigned int getWidth() const;

		//Function to get height
		unsigned int getHeight() const;

		void close() const;
	};
}