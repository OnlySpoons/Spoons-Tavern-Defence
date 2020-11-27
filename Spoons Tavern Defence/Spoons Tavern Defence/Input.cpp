#include "Input.h"

//Initial variable declaration
bool Input::_Initialised = false;

//Initialisation function, to emulate a constructor
void Input::init(Camera* cam, unsigned int width, unsigned int height)
{
	if (!_Initialised)
	{
		_Camera		 = cam;
		_LastX		 = (float)width / 2.0f;
		_LastY		 = (float)height / 2.0f;
		_FirstMouse  = true;

		_Initialised = true;
	}
}

//Function to check if Input has been initialised
void Input::checkInit()
{
	if (!_Initialised)
	{
		throw "Input is not initialised";
	}
}

//Function to process user input
void Input::processInput(GLFWwindow* window, float deltaTime)
{
	checkInit();

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		_Camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		_Camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		_Camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		_Camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
}

//Window resizing callback
void Input::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	checkInit();

	//Make sure the viewport matches the new window dimensions; note that width and 
	//height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

//Callback function to handle mouse movement
void Input::mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	checkInit();

	if (Input::_FirstMouse)
	{
		_LastX		= (float)xPos;
		_LastY		= (float)yPos;
		_FirstMouse = false;
	}

	float xOffset = (float)xPos - _LastX;
	float yOffset = _LastY - (float)yPos; //Reversed since y-coordinates go from bottom to top

	_LastX = (float)xPos;
	_LastY = (float)yPos;

	_Camera->ProcessMouseMovement(xOffset, yOffset);
}

//Callback function to handle scroll wheel usage
void Input::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	checkInit();

	_Camera->ProcessMouseScroll((float)yOffset);
}