#include <iostream>

#include "Window.h"
#include "Input.h"

//Constants for screen dimensions
constexpr unsigned int SCR_WIDTH = 1280;
constexpr unsigned int SCR_HEIGHT = 640;

// move to player when created
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
	try {
		// Move to player?
		Input::init(&camera, SCR_WIDTH, SCR_HEIGHT);

		//declare and create window instance
		Window window(SCR_WIDTH, SCR_HEIGHT, "Spoons: Tavern Defence");

		while (!glfwWindowShouldClose(window.instance))
		{
			std::cout << "I'm working!!!" << std::endl;
		}
	}
	catch (const char* exceptionMessage)
	{
		std::cout << exceptionMessage << std::endl;
	}
}