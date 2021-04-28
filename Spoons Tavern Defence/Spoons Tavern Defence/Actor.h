#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Model.h"
#include "RigidBody.h"

#include "Input.h"
#include "KeyCode.h"
#include "MouseCode.h"

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

		//Member variables
	public:
		Camera* _camera;

	protected:
		Model _model;
		RigidBody _rigidBody;

		//Fuctions
	public:

		//Constructor
		Actor(const Transform& data,
			Camera* camera,
			const std::string& modelPath = ""
		);

		//Destructor
		virtual ~Actor();

		//Render the object
		void draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass);

		//Update the object
		virtual void update(float& deltaTime) = 0;

		virtual void physicsUpdate() = 0;

		bool onGround();
	};
}