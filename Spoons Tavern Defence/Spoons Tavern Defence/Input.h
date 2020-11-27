#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include"Camera.h"

//A static class to handle user input (Must be static for callback functions to work correctly).
class Input
{

//Member variables
private:
	static bool _Initialised;

	static Camera *_Camera;
	static float _LastX;
	static float _LastY;
	static bool _FirstMouse;

//Functions
public:

	//Initialisation function, to emulate a constructor
	static void init(Camera *cam, unsigned int width, unsigned int height);

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