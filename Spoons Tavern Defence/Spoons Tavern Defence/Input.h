#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include "KeyCode.h"
#include "MouseCode.h"

namespace spty {
	class Window;

	//A static class to handle user input
	class Input
	{
	//Variables
	private:
		static Window* window_;

		static glm::vec2 scrollOffset_;
		static glm::vec2 lastPos_;
		static bool firstMouse_;

	//Functions
	public:
		static bool isKeyPressed(KeyCode key);
		static bool isKeyHeld(KeyCode key);
		static bool isKeyReleased(KeyCode key);

		static bool isButtonPressed(MouseCode button);
		static bool isButtonHeld(MouseCode button);
		static bool isButtonReleased(MouseCode button);

		static glm::vec2 getCursorPos();
		static glm::vec2 getCursorOffset();
		static glm::vec2 getScrollOffset() { return scrollOffset_; }

		static void setWindow(Window* window) { window_ = window; }
		static void clearWindow() { window_ = nullptr; }
		static void checkWindow() { if (!window_) throw "Input has no assigned Window"; }
		static void closeWindow();


		//Window resizing callback
		static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
		{ glViewport(0, 0, width, height); }

		//Scroll wheel usage callback
		static void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
		{ scrollOffset_ = glm::vec2((float)xOffset, (float)yOffset); }
	};
}