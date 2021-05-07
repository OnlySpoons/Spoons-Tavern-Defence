#include "Input.h"
#include "Window.h"

namespace spty {

	//Initial variable declaration
	Window* Input::window_ = nullptr;
	glm::vec2 Input::scrollOffset_ = glm::vec2(0.0f);
	glm::vec2 Input::lastPos_ = glm::vec2(0.0f);
	bool Input::firstMouse_ = true;

	bool Input::isKeyPressed(KeyCode key)
	{
		checkWindow();
		return glfwGetKey(window_->getInstance(), (int)key) == GLFW_PRESS;
	}

	bool Input::isKeyHeld(KeyCode key)
	{
		checkWindow();
		return glfwGetKey(window_->getInstance(), (int)key) == GLFW_REPEAT;
	}

	bool Input::isKeyReleased(KeyCode key)
	{
		checkWindow();
		return glfwGetKey(window_->getInstance(), (int)key) == GLFW_RELEASE;
	}

	
	bool Input::isButtonPressed(MouseCode button)
	{
		checkWindow();
		return glfwGetMouseButton(window_->getInstance(), (int)button) == GLFW_PRESS;
	}

	bool Input::isButtonHeld(MouseCode button)
	{
		checkWindow();
		return glfwGetMouseButton(window_->getInstance(), (int)button) == GLFW_REPEAT;
	}

	bool Input::isButtonReleased(MouseCode button)
	{
		checkWindow();
		return glfwGetMouseButton(window_->getInstance(), (int)button) == GLFW_RELEASE;
	}


	glm::vec2 Input::getCursorPos()
	{
		checkWindow();
		double xPos, yPos;
		glfwGetCursorPos(window_->getInstance(), &xPos, &yPos);
		return glm::vec2((float)xPos, (float)yPos);
	}

	glm::vec2 Input::getCursorOffset()
	{
		glm::vec2 mousePos = getCursorPos();

		if (firstMouse_)
		{
			lastPos_ = mousePos;
			firstMouse_ = false;
		}

		float xOffset = mousePos.x - lastPos_.x;
		float yOffset = lastPos_.y - mousePos.y; //Reversed since y-coordinates go from bottom to top

		lastPos_ = mousePos;

		return glm::vec2(xOffset, yOffset) * 0.1f;
	}

	void Input::closeWindow()
	{
		checkWindow();
		window_->close();
	}
}