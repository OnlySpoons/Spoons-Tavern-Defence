#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/transform.hpp>

#include "WorldDirections.h"

namespace spty {
	enum class Axis
	{
		X = 0,
		Y,
		Z
	};

	class Transform
	{
		
	//Variables
	private:
		glm::vec3 pos_;
		glm::vec3 rot_;
		glm::vec3 scale_;
		float angularVelocity_ = 0.0f;

	//Functions
	public:
		//Constructor
		Transform(const glm::vec3& pos = glm::vec3(0.0f), const glm::vec3& rot = glm::vec3(0.0f), const glm::vec3& scale = glm::vec3(1.0f));

		//Descturctor
		virtual ~Transform();

		//Getters
		glm::vec3 getPosition() const { return pos_; }
		glm::vec3 getScale() const { return scale_; }
		glm::vec3 getRotation() const { return rot_; }
		float getAngularVelocity() const { return angularVelocity_; }

		glm::vec3 getFront() const;
		glm::vec3 getRight() const;
		glm::vec3 getUp() const;

		glm::mat4 getMatrix() const;

		float getPitch() const { return rot_.y; }
		float getYaw() const { return rot_.x; }
		float getRoll() const { return rot_.z; }

		//Setters
		void setPosition(const glm::vec3& translation) { pos_ = translation; }
		void setScale(const glm::vec3& scaling) { scale_ = scaling; }
		void setRotation(const glm::vec3& rotation) { rot_ = rotation; constrainPitch(); }
		void setAngularVelocity(float angularVelocity) { angularVelocity_ = angularVelocity; }

		void setPitch(float pitch) { rot_.y = pitch; }
		void setYaw(float yaw) { rot_.x = yaw; }
		void setRoll(float roll) { rot_.z = roll; }

	//Utility functions
	public:
		void move(const glm::vec3& dir) { pos_ += dir; }
		void addAngularVelocity(float amount) { angularVelocity_ += amount; }

		//Rotation functions
		void rotate(const float& angle, Axis axis);
		void pitch(const float& angle) { rot_.y += angle; constrainPitch(); }
		void yaw(const float& angle) { rot_.x += angle; }
		void roll(const float& angle) { rot_.z += angle; }

	private:
		void constrainPitch();
	};
}