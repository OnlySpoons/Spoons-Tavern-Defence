#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <glm/glm.hpp>
#include <bullet/btBulletCollisionCommon.h>
#include <bullet/BulletCollision/CollisionShapes/btShapeHull.h>

#include "Physics.h"

namespace spty {
	class PhysicsMaterial
	{
	public:
		float friction_;
		float bounciness_;

	public:
		PhysicsMaterial();
		PhysicsMaterial(float f, float b);
	};

	class Collider
	{
		friend class RigidBody;
		friend class Physics;

	protected:
		btCollisionShape* shape_;
		PhysicsMaterial material_;

	public:
		Collider() : shape_(nullptr) {}

		virtual ~Collider() { delete shape_; }

		btCollisionShape* getShape() { return shape_; }

	private:
		virtual void generateShape() = 0;
	};

	class BoxCollider : public Collider
	{
	private:
		glm::vec3 size_;

	public:
		BoxCollider();
		BoxCollider(glm::vec3 s);

		void setSize(glm::vec3 s) { size_ = s; generateShape(); }

		glm::vec3 getSize() { return size_; }
		
		void generateShape() override;
	};

	class SphereCollider : public Collider
	{
	private:
		float radius_;

	public:
		SphereCollider();
		SphereCollider(float r);

		void setRadius(float r) { radius_ = r; generateShape(); }

		float getRadius() { return radius_; }

		void generateShape() override;
	};

	class CapsuleCollider : public Collider
	{
	private:
		float radius_;
		float height_;

	public:
		CapsuleCollider();
		CapsuleCollider(float r, float h);

		void generateShape() override;
	};

	class MeshCollider : public Collider
	{
	private:
		btTriangleMesh mesh_;

	public:
		MeshCollider();
		MeshCollider(const btTriangleMesh& m);

		//Recreates the bullet collision shape
		void generateShape() override;
	};

	class CompoundCollider : public Collider
	{
	private:
		std::vector<Collider*> colliders_;
		std::vector<glm::mat4> transforms_;

	public:
		CompoundCollider();
		CompoundCollider(const std::vector<Collider*>& colliders, const std::vector<glm::mat4>& transforms);

		void addCollider(Collider* collider, glm::mat4 transform);

		void generateShape() override;
	};

}