#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include "Shader.h"
#include "PassType.h"
#include "Transform.h"

namespace spty {
	class GameObject
	{
	//Variables
	public:
		Transform transform_;
		bool isEnabled_;

	//Functions
	public:
		//Constructors
		GameObject() :transform_(Transform()), isEnabled_(false) {}
		GameObject(const Transform& data, const bool& enabled = false)
			: transform_(data), isEnabled_(enabled) {}

		//Destructor
		virtual ~GameObject() {}

		virtual void draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass) = 0;

		virtual void update(float& deltaTime) = 0;
		virtual void physicsUpdate() = 0;

		void enable() { isEnabled_ = true;}
		void disable() { isEnabled_ = false; }
	};
}