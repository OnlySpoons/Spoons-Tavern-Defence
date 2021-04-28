#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "KeyCode.h"
#include "MouseCode.h"

namespace spty {

	//A promise that the Window class will exist (avoids include loop)
	class Window;
	class Actor;

	//A static class to handle user input (Must be static for callback functions to work correctly).
	class Input
	{

		//Member variables
	private:
		//Reference to the window
		static Window* _window;

		static glm::vec2 _scrollOffset;
		static glm::vec2 _lastPos;
		static bool firstMouse;

		//Functions
	public:

		//Functions to set member variables
		static void setWindow(Window* window);

		//Functions to check if window is set
		static void checkWindow();

		//Functions to check for key input
		static bool isKeyPressed(KeyCode key);
		static bool isKeyHeld(KeyCode key);
		static bool isKeyReleased(KeyCode key);

		//Functions to get mouse button input
		static bool isButtonPressed(MouseCode button);
		static bool isButtonHeld(MouseCode button);
		static bool isButtonReleased(MouseCode button);

		//Function to get cursor positon
		static glm::vec2 getCursorPos();

		//Function to get cursor offset
		static glm::vec2 getCursorOffset();

		//Function to get scroll offset
		static glm::vec2 getScrollOffset();

		//TODO: remove this function when events are implimented
		//Function to close the window
		static void closeWindow();

		//Function to clear the window pointer
		static void clearWindow();

		//Window resizing callback
		static void framebufferSizeCallback(GLFWwindow* window, int width, int height);

		//Callback function to handle scroll wheel usage
		static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

		//Callback function to handle mouse
		//static void mouseCallback(GLFWwindow* window, double xpos, double ypos);
	};
}