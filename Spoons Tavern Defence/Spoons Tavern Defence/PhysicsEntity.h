#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include "Entity.h"
#include "RigidBody.h"

namespace spty {
	class PhysicsEntity : public Entity
	{
	//Variables
	protected:
		RigidBody rigidBody_;

	//Functions
	public:
		//Constructors
		PhysicsEntity() {}
		PhysicsEntity(const Transform& data, Model* model, Collider* collider = nullptr);

		//Destructor
		virtual ~PhysicsEntity();

		virtual void draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass) override;

		virtual void update(float& deltaTime) override {}
		virtual void physicsUpdate() override;

		//Getters
		RigidBody getRigidBody() const { return rigidBody_; }

		//Setters
		void setRigidBody(const RigidBody& rigidBody) { rigidBody_ = rigidBody; }
		void setKinematic(bool val) { rigidBody_.setKinematic(val); }
	};
}