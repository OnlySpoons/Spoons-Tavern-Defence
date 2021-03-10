#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <glm/gtx/transform.hpp>

#include "WorldDirections.h"

namespace Spoonity {

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
		glm::vec3 _pos;
		glm::vec3 _rot;
		glm::vec3 _scale;

	//Functions
	public:
		//Constructor
		Transform(const glm::vec3& pos = glm::vec3(0.0f),
			const glm::vec3& rot = glm::vec3(0.0f),
			const glm::vec3& scale = glm::vec3(1.0f));

		//Descturctor
		virtual ~Transform();

		//Setters for transform data
		void setPosition(const glm::vec3& translation);
		void setScale(const glm::vec3& scaling);
		void setRotation(const glm::vec3& rotation);

		//Getters for transform data
		glm::vec3 getPosition() const;
		glm::vec3 getScale() const;
		glm::vec3 getRotation() const;

		//Getters for direction vectors
		glm::vec3 getRight() const;
		glm::vec3 getUp() const;
		glm::vec3 getFront() const;

		//Getter for the transform matrix
		glm::mat4 getMatrix() const;

	//Utility functions
	public:

		void move(const glm::vec3& dir);

		//Rotation functions
		void rotate(const float& angle, Axis axis);
		void pitch(const float& angle);
		void yaw(const float& angle);
		void roll(const float& angle);

		//Getters for specific rotations
		float getPitch() const;
		float getYaw() const;
		float getRoll() const;

	private:
		//Keep pitch from inverting
		void constrainPitch();
	};

}