#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include "GameObject.h"
#include "Camera.h"
#include "Model.h"
#include "RigidBody.h"

#include "Input.h"

namespace spty {

	//Abstraction for possible directions of movement
	enum class Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	class Actor : public GameObject
	{
	//Variables
	public:
		Camera* camera_;

	protected:
		Model model_;
		RigidBody rigidBody_;

	//Fuctions
	public:
		//Constructor
		Actor(const Transform& data, Camera* camera, const std::string& modelPath = "");

		//Destructor
		virtual ~Actor();

		void draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass);

		virtual void update(float& deltaTime) = 0;
		virtual void physicsUpdate() = 0;

		bool onGround() const;
	};
}