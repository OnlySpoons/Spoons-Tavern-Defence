#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace GameEngine {

	//Abstraction for possible directions of camera movement
	enum class Camera_Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	//Default values for major variables
	constexpr float YAW = -90.0f;
	constexpr float PITCH = 0.0f;
	constexpr float SPEED = 2.5f;
	constexpr float SENSITIVITY = 0.1f;
	constexpr float ZOOM = 45.0f;

	class Camera
	{

		//Member variables
	public:
		glm::vec3 _Position;
		glm::vec3 _Front;
		glm::vec3 _Up;
		glm::vec3 _Right;
		glm::vec3 _WorldUp;

		float _Yaw;
		float _Pitch;

		float _MovementSpeed;
		float _MouseSensitivity;
		float _Zoom;

		//Functions
	public:

		//Constructor
		Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);

		//Returns the direction the player is looking to translate objects into view space
		glm::mat4 GetViewMatrix() const;

		//Processes the keyboard input to control camera movement
		void ProcessKeyboard(Camera_Movement direction, float deltaTime, bool isSptinting);

		//Processes the mouse movement to control where the camera is facing
		void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);

		//Processes the scroll wheel to control the zoom]
		void ProcessMouseScroll(float yoffset);

	private:

		//Reacalculates the cameras direction vectors
		void updateCameraVectors();
	};
}