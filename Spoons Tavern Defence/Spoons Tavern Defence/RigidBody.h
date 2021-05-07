#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>
#include <glm/fwd.hpp>

#include "Physics.h"
#include "Collider.h"

namespace spty {
	class RigidBody
	{
		friend class Physics;

	//Variables
	private:
		glm::vec3 inertia_ = PhysicsConstants::INERTIA;
		bool kinematic_ = PhysicsConstants::KINEMATIC;
		float mass_ = 10.0f;

		//Bullet implementation
		btRigidBody* body_ = nullptr;
		Collider* collider_ = nullptr;

	//Functions
	public:
		//Constructors
		RigidBody() {}
		RigidBody(const Transform& transform, Collider* col);

		//Destructor
		~RigidBody();

		void setMass(float m);
		void setForce(glm::vec3 f);
		void setKinematic(bool val);
		void setLinearDamping(float val);

		void move(glm::vec3 direction);

		btTransform getWorldTransform(); //Needs testing
		glm::vec3 getBulletPosition();
		glm::vec3 getBulletRotation();
		glm::vec3 getBulletInertia();
		const btRigidBody* getBulletBody() const { return body_; }

		void calculateLocalInertia();

		void disableGravity();
		void enableGravity();
	};
}