#include "Input.h"

Camera* Input::camera = nullptr;
float Input::lastX = 0.0f;
float Input::lastY = 0.0f;
bool Input::firstMouse = true;

//Initialisation function
void Input::init(Camera* cam, unsigned int width, unsigned int height) {
	camera = cam;
	lastX = (float)width / 2.0f;
	lastY = (float)height / 2.0f;
}

//Function to check if Input has been initialised
void Input::checkInit()
{
	if (camera == nullptr)
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
		camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);

	float heightScale = 0.1f;

	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		if (heightScale > 0.0f)
			heightScale -= 0.0005f;
		else
			heightScale = 0.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		if (heightScale < 1.0f)
			heightScale += 0.0005f;
		else
			heightScale = 1.0f;
	}
}

//Window resizing Callback
void Input::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	checkInit();

	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

//Mouse Callback
void Input::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	checkInit();

	if (Input::firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos; // reversed since y-coordinates go from bottom to top

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera->ProcessMouseMovement(xoffset, yoffset);
}

//Scroll wheel callback
void Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	checkInit();

	camera->ProcessMouseScroll((float)yoffset);
}