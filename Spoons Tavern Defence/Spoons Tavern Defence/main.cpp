#include <iostream>

#include "Window.h"
#include "Input.h"

/*
Conventions:

----Variables----
constants = CAPITALISED_VARIABLE
Member variables    = _Variable
Function parameters = camelCase
Temporary variables = camelCase

Related variables should be grouped
Unrelated variables should be separated by a new line
Variable assignement in groups should be lined up vertically

----Functions----
Function names = camelCase

Member variables and Functions have separate access modifier headings
Functions called by other functions should be declared higher up
Similar functions should be grouped together
Functions that don't modify member variables should be declared as const where possible

----Structs----
Struct declarations = StructName

----Comments----
Access modifier headings should have comments if they are the start of variable declaration or functions declaration
Functions should have comments above them with a brief description
*/

//Constants for screen dimensions
constexpr unsigned int SCR_WIDTH = 1280;
constexpr unsigned int SCR_HEIGHT = 720;

//Move to player when created
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

int main()
{
	try {
		//Move to player?
		Input::init(&camera, SCR_WIDTH, SCR_HEIGHT);

		//Declare and create window instance
		Window window(WindowProps("Spoons: Tavern Defence", SCR_WIDTH, SCR_HEIGHT));

		while (!glfwWindowShouldClose(window._Instance))
		{
			std::cout << "Window initialised and working!" << std::endl;
		}
	}
	//Catch and display thrown exceptions in console
	catch (const char* exceptionMessage)
	{
		std::cout << exceptionMessage << std::endl;
	}
}