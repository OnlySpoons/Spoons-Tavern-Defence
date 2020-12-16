#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include"Actor.h"

namespace Spoonity{

	//A static class to handle user input (Must be static for callback functions to work correctly).
	class Input
	{

	//Member variables
	public:
		static bool _Initialised;

		//TODO - add player class
		//static std::vector<Player*> players;

		static Actor* _Player;
		static float _LastX;
		static float _LastY;
		static bool _FirstMouse;

	//Functions
	public:

		//Initialisation function, to emulate a constructor
		static void init(Actor* player);

		//Function to check if Input has been initialised
		static void checkInit();

		//Function to process user input
		static void processInput(GLFWwindow* window, float deltaTime);

		//Window resizing callback
		static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

		//Callback function to handle mouse movement
		static void mouseCallback(GLFWwindow* window, double xPos, double yPos);

		//Callback function to handle scroll wheel usage
		static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	};
}