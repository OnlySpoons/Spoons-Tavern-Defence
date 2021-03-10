#pragma once

#include <bullet/btBulletCollisionCommon.h>
#include <bullet/btBulletDynamicsCommon.h>

#include <glm/fwd.hpp>

#include "Collider.h"

#include "Physics.h"

namespace Spoonity {

	class RigidBody
	{
		friend class Physics;
	public:
		//Default constructor
		RigidBody() {}
		RigidBody(GameObject* obj, BoxCollider* col)
			: collider(col) 
		{
			localData = obj->_Data;
		}
		~RigidBody() {}

		void init();

		void setMass(float m);
		void setForce(glm::vec3 f);
		void setKinematic(bool val);

		btTransform getWorldTransform(); //Needs testing
		glm::vec3 getBulletPosition();
		glm::vec3 getBulletRotation();

	private:
		glm::vec3 inertia = PhysicsConstants.INERTIA;
		bool kinematic = PhysicsConstants.KINEMATIC;
		float mass = PhysicsConstants.MASS;

		//Bullet implementation
		btRigidBody* body = nullptr;
		GameObject::_Data localData; //TODO: need way of storing copy of constructor's obj._Data for updating pos/rot
		BoxCollider* collider = nullptr;
	};

}