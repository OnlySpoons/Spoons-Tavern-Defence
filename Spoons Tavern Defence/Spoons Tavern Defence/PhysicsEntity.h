#pragma once

#include "Entity.h"
#include "RigidBody.h"

namespace spty {

	class PhysicsEntity : public Entity
	{
	//Variables
	protected:
		RigidBody _rigidBody;

	//Functions
	public:

		//Constructors
		PhysicsEntity() {}

		PhysicsEntity(const Transform& data,
			Model* model,
			Collider* collider = nullptr
		);

		virtual ~PhysicsEntity();

		virtual void draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass) override;

		virtual void update(float& deltaTime) override {}

		virtual void physicsUpdate() override;

		RigidBody getRigidBody() const { return _rigidBody; }

		void setRigidBody(const RigidBody& rigidBody) { _rigidBody = rigidBody; }

		void setKinematic(bool val) { _rigidBody.setKinematic(val); }
	};
}