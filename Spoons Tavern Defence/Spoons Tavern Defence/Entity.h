#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Model.h"
#include "RigidBody.h"

namespace spty {

	class Entity : public GameObject
	{
		//Variables
	private:
		//Entities control their own model
		Model _model;
		RigidBody _rigidBody;

		//Functions
	public:

		//Constructors
		Entity() {}

		Entity(const Transform& data,
			const std::string& modelPath = ""
		);

		//Render the object
		virtual void draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass) override;

		//Unused by skybox
		virtual void update(float& deltaTime) override;

		virtual void physicsUpdate() override;

		RigidBody getRigidBody() const { return _rigidBody; }

		void setRigidBody(RigidBody rigidBody) { _rigidBody = rigidBody; }

		void setKinematic(bool val) { _rigidBody.setKinematic(val); }
	};
}