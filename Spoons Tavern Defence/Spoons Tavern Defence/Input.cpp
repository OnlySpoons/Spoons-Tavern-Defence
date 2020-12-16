#include "Input.h"

namespace Spoonity {

	//Initial variable declaration
	Actor* Input::_Player = nullptr;
	float Input::_LastX = 0.0f;
	float Input::_LastY = 0.0f;
	bool Input::_FirstMouse = true;

	bool Input::_Initialised = false;

	//Initialisation function, to emulate a constructor
	void Input::init(Actor* player)
	{
		if (!_Initialised)
		{
			_Player = player;
			
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

	static bool isSprinting = false;
	//Function to process user input
	void Input::processInput(GLFWwindow* window, float deltaTime)
	{
		checkInit();

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
			isSprinting = true;
		else
			isSprinting = false;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			_Player->ProcessKeyboard(Movement::FORWARD, deltaTime, isSprinting);
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			_Player->ProcessKeyboard(Movement::BACKWARD, deltaTime, isSprinting);
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			_Player->ProcessKeyboard(Movement::LEFT, deltaTime, isSprinting);
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			_Player->ProcessKeyboard(Movement::RIGHT, deltaTime, isSprinting);
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

		if (_FirstMouse)
		{
			_LastX = (float)xPos;
			_LastY = (float)yPos;
			_FirstMouse = false;
		}

		float xOffset = (float)xPos - _LastX;
		float yOffset = _LastY - (float)yPos; //Reversed since y-coordinates go from bottom to top

		_LastX = (float)xPos;
		_LastY = (float)yPos;

		_Player->ProcessMouseMovement(xOffset, yOffset);
	}

	//Callback function to handle scroll wheel usage
	void Input::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		checkInit();

		_Player->ProcessMouseScroll((float)yOffset);
	}
}