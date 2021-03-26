#pragma once

#include <glm/glm.hpp>
#include <bullet/btBulletCollisionCommon.h>

#include "Physics.h"

namespace Spoonity {

	class PhysicsMaterial
	{
		float friction;
		float bounciness;

		PhysicsMaterial();
		PhysicsMaterial(float f, float b = PhysicsConstants.BOUNCE);
	};

	class Collider
	{
		friend class RigidBody;
		friend class Physics;

	public:
		~Collider() {}

		void setCentre(glm::vec3 c);
		glm::vec3 getCentre();

	protected:
		btCollisionShape* shape;
		PhysicsMaterial material;
		glm::vec3 centre;

		//May need to add: int tag;

	};

	class BoxCollider : public Collider
	{
	public:
		BoxCollider();
		BoxCollider(glm::vec3 s, glm::vec3 c);

		void setSize(glm::vec3 s);

		glm::vec3 getSize();

	private:
		glm::vec3 size;

		//Recreates the bullet collision shape
		void generateShape();
	};

	class SphereCollider : public Collider
	{
	public:
		SphereCollider();
		SphereCollider(float r, glm::vec3 c);

		void setRadius(float r);

		float getRadius();

	private:
		float radius;

		//Recreates the bullet collision shape
		void generateShape();
	};

}