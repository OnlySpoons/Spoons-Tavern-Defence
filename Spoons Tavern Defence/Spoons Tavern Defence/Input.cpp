#include "Input.h"
#include "Window.h"
#include "Actor.h"

namespace Spoonity {

	//Initial variable declaration
	Window* Input::_window = nullptr;
	glm::vec2 Input::_scrollOffset = glm::vec2(0.0f);

	void Input::setWindow(Window* window)
	{
		_window = window;
	}

	//Function to check if Input has been initialised
	void Input::checkWindow()
	{
		if (!_window)
		{
			throw "Input has no assigned Window";
		}
	}

	//Functions to check for key input
	bool Input::isKeyPressed(KeyCode key)
	{
		checkWindow();

		return glfwGetKey(_window->getInstance(), (int)key) == GLFW_PRESS;
	}

	bool Input::isKeyHeld(KeyCode key)
	{
		return glfwGetKey(_window->getInstance(), (int)key) == GLFW_REPEAT;
	}

	bool Input::isKeyReleased(KeyCode key)
	{
		checkWindow();

		return glfwGetKey(_window->getInstance(), (int)key) == GLFW_RELEASE;
	}

	//Functions to get mouse button input
	bool Input::isButtonPressed(MouseCode button)
	{
		checkWindow();

		return glfwGetMouseButton(_window->getInstance(), (int)button) == GLFW_PRESS;
	}

	bool Input::isButtonHeld(MouseCode button)
	{
		checkWindow();

		return glfwGetMouseButton(_window->getInstance(), (int)button) == GLFW_REPEAT;
	}

	bool Input::isButtonReleased(MouseCode button)
	{
		checkWindow();

		return glfwGetMouseButton(_window->getInstance(), (int)button) == GLFW_RELEASE;
	}

	//Function to get cursor positon
	glm::vec2 Input::getCursorPos()
	{
		checkWindow();

		double xPos, yPos;

		glfwGetCursorPos(_window->getInstance(), &xPos, &yPos);

		return glm::vec2((float)xPos, (float)yPos);
	}

	//Function to get scroll offset
	glm::vec2 Input::getScrollOffset()
	{
		return _scrollOffset;
	}

	//TODO: remove this function
	//Function to close the window
	void Input::closeWindow()
	{
		_window->close();
	}

	//Function to clear the window pointer
	void Input::clearWindow()
	{
		_window = nullptr;
	}

	//Window resizing callback
	void Input::framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		//Make sure the viewport matches the new window dimensions; note that width and 
		//height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}

	//Callback function to handle scroll wheel usage
	void Input::scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
	{
		_scrollOffset.x = (float)xOffset;
		_scrollOffset.y = (float)yOffset;
	}
}