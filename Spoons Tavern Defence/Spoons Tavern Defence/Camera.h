#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Transform.h"

namespace spty {


	class Camera
	{
	//Variables
	private:
		static constexpr float YAW = -90.0f;
		static constexpr float PITCH = 0.0f;
		static constexpr float FOV = 90.0f;

		glm::vec3 position_;
		glm::vec3 front_, up_;
		float fov_;

	//Functions
	public:
		//Constructor
		Camera(glm::vec3 position	= glm::vec3(0.0f),
			   glm::vec3 front		= WorldDir::FRONT,
			   glm::vec3 up			= WorldDir::UP,
			   float fov			= FOV );
		
		void update(const Transform& transform, const glm::vec3& cameraOffset = glm::vec3(0.0f));

		//Getters
		glm::vec3 getPosition() const { return position_; }
		glm::vec3 getFront() const { return front_; }
		glm::vec3 getUp() const { return up_; }
		float getFOV() const { return fov_; }
		
		//Returns the transform matrix of objects into view space
		glm::mat4 GetViewMatrix() const { return glm::lookAt(position_, position_ + front_, up_); }

		//Setters
		void setPosition(const glm::vec3& position) { position_ = position; }
		void setFront(const glm::vec3& front) { front_ = front; }
		void setUp(const glm::vec3& up) { up_ = up; }
		void setFOV(const float& fov) { fov_ = fov; }

	};
}