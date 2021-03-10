#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Transform.h"

namespace Spoonity {

	//Default values for major variables
	constexpr float YAW = -90.0f;
	constexpr float PITCH = 0.0f;

	class Camera
	{
	//Variables
	private:
		static constexpr float FOV = 90.0f;

		glm::vec3 _position;
		glm::vec3 _front;
		glm::vec3 _up;
		float _fov;

	//Functions
	public:

		//Constructor
		Camera(glm::vec3 position = glm::vec3(0.0f),
			   glm::vec3 front = WorldDir::FRONT,
			   glm::vec3 up = WorldDir::UP,
			   float fov = FOV
		);
		
		//Update all variables
		void update(const Transform& transform, const glm::vec3& cameraOffset = glm::vec3(0.0f));

		//Setters
		void setPosition(const glm::vec3& position);
		void setFront(const glm::vec3& front);
		void setUp(const glm::vec3& up);
		void setFOV(const float& fov);

		//Getters
		glm::vec3 getPosition() const;
		glm::vec3 getFront() const;
		glm::vec3 getUp() const;
		float getFOV() const;


		//Returns the direction the player is looking to translate objects into view space
		glm::mat4 GetViewMatrix() const;
	};
}