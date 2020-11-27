/*
Conventions:

----Variables----
constants = CAPITALISED_VARIABLE
Member variables    = _CamelCase
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

----Shaders----
Shader names = shader_name.vs/fs/gs
*/

#include <iostream>

#include "Engine.h"

using namespace GameEngine;

int main()
{
	try {
		Engine* engine = new Engine();

		while (engine->isRunning())
		{
			engine->runtimeLoop();

			//std::cout << "Engine is running!" << std::endl;
		}

		delete engine;
		return 0;
	}
	//Catch and display thrown exceptions in console
	catch (const char* exceptionMessage)
	{
		std::cout << exceptionMessage << std::endl;
		return -1;
	}
}