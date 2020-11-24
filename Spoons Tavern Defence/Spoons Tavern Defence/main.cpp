#include "Window.h"

int main()
{
	//declare and create window instance
	Window window;
	window.Create("Spoons: Tavern Defence");

	while (!glfwWindowShouldClose(window.instance))
	{
		std::cout << "I'm working!!!" << std::endl;
	}
}