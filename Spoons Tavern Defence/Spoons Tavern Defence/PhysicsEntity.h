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
			const std::string& modelPath,
			Collider* collider = nullptr
		);

		virtual ~PhysicsEntity() {}

		virtual void update(float& deltaTime) override;

		virtual void physicsUpdate() override;

		RigidBody getRigidBody() const { return _rigidBody; }

		void setRigidBody(const RigidBody& rigidBody) { _rigidBody = rigidBody; }

		void setKinematic(bool val) { _rigidBody.setKinematic(val); }
	};
}