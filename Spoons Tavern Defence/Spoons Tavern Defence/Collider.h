#pragma once
#include <glm/glm.hpp>
#include <bullet/btBulletCollisionCommon.h>
#include <bullet/BulletCollision/CollisionShapes/btShapeHull.h>

#include "Physics.h"

namespace spty {

	class PhysicsMaterial
	{
	public:
		float _friction;
		float _bounciness;

	public:
		PhysicsMaterial();
		PhysicsMaterial(float f, float b);
	};

	class Collider
	{
		friend class RigidBody;
		friend class Physics;

	public:
		Collider() : _shape(nullptr) {}

		virtual ~Collider() { delete _shape; }

		btCollisionShape* getShape() { return _shape; }

	protected:
		btCollisionShape* _shape;
		PhysicsMaterial _material;

	private:
		virtual void generateShape() = 0;

		//May need to add: int tag;

	};

	class BoxCollider : public Collider
	{
	public:
		BoxCollider();
		BoxCollider(glm::vec3 s);

		void setSize(glm::vec3 s);

		glm::vec3 getSize();

	private:
		glm::vec3 _size;

		//Recreates the bullet collision shape
		void generateShape() override;
	};

	class SphereCollider : public Collider
	{
	public:
		SphereCollider();
		SphereCollider(float r);

		void setRadius(float r);

		float getRadius();

	private:
		float _radius;

		//Recreates the bullet collision shape
		void generateShape() override;
	};

	class CapsuleCollider : public Collider
	{
	public:
		CapsuleCollider();
		CapsuleCollider(float r, float h);

	private:
		float _radius;
		float _height;

		void generateShape() override;
	};

	class MeshCollider : public Collider
	{
	public:
		MeshCollider();
		MeshCollider(const btTriangleMesh& m);

	private:
		btTriangleMesh _mesh;

		//Recreates the bullet collision shape
		void generateShape() override;
	};

	class CompoundCollider : public Collider
	{
	public:
		CompoundCollider();
		CompoundCollider(const std::vector<Collider*>& colliders, const std::vector<glm::mat4>& transforms);

		void addCollider(Collider* collider, glm::mat4 transform);

	private:
		std::vector<Collider*> _colliders;
		std::vector<glm::mat4> _transforms;

		void generateShape() override;
	};

}