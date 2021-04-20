#pragma once

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>

#include <glm/fwd.hpp>

#include "Collider.h"

#include "Physics.h"

namespace spty {

	class RigidBody
	{
		friend class Physics;
	public:
		//Default constructor
		RigidBody() {}
		
		RigidBody(const Transform& transform, Collider* col);

		~RigidBody();

		void setMass(float m);
		void setForce(glm::vec3 f);
		void setKinematic(bool val);

		void move(glm::vec3 direction);

		btTransform getWorldTransform(); //Needs testing
		glm::vec3 getBulletPosition();
		glm::vec3 getBulletRotation();
		glm::vec3 getBulletInertia();

		void calculateLocalInertia();

	private:
		glm::vec3 _inertia = PhysicsConstants::INERTIA;
		bool _kinematic = PhysicsConstants::KINEMATIC;
		float _mass = 10.0f;

		//Bullet implementation
		btRigidBody* _body = nullptr;
		Collider* _collider = nullptr;
	};
}