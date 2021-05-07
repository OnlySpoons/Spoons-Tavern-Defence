#include "Collider.h"

namespace spty {

	//Physics Material Constructors
	PhysicsMaterial::PhysicsMaterial(float f, float b)
	{
		friction_ = f;
		bounciness_ = b;
	}
	PhysicsMaterial::PhysicsMaterial() 
	{
		friction_ = PhysicsConstants::FRICTION;
		bounciness_ = 0.0f;
	}

	//Box Collider Constructors
	BoxCollider::BoxCollider()
	{ 
		size_ = glm::vec3(1.0f, 1.0f, 1.0f);
		generateShape();
	}
	BoxCollider::BoxCollider(glm::vec3 s)
	{ 
		size_ = s;
		generateShape();
	}

	//Sphere Collider Constructors
	SphereCollider::SphereCollider() 
	{ 
		radius_ = 1.0f;
		generateShape();
	}
	SphereCollider::SphereCollider(float r)
	{ 
		radius_ = r;
		generateShape();
	}

	//Capsule Collider Constructors
	CapsuleCollider::CapsuleCollider()
	{
		radius_ = 0.5f;
		height_ = 1.0f;
		generateShape();
	}
	CapsuleCollider::CapsuleCollider(float r, float h)
	{
		radius_ = r;
		height_ = h;
		generateShape();
	}

	//Mesh Collider Constuctors
	MeshCollider::MeshCollider()
	{
		mesh_ = btTriangleMesh();
		generateShape();
	}
	MeshCollider::MeshCollider(const btTriangleMesh& m)
	{
		mesh_ = m;
		generateShape();
	}

	//Compound Collider Constructors
	CompoundCollider::CompoundCollider()
	{
		colliders_ = {};
		transforms_ = {};
		generateShape();
	}
	CompoundCollider::CompoundCollider(const std::vector<Collider*>& colliders, const std::vector<glm::mat4>& transforms)
	{
		colliders_ = colliders;
		transforms_ = transforms;
		generateShape();
	}


	void BoxCollider::generateShape() { shape_ = new btBoxShape(Physics::glmVec3TobtVector3(size_)); }
	void SphereCollider::generateShape() { shape_ = new btSphereShape(radius_); }
	void CapsuleCollider::generateShape() { shape_ = new btCapsuleShape(radius_, height_); }

	void MeshCollider::generateShape()
	{
		btConvexTriangleMeshShape convexShape = btConvexTriangleMeshShape(&mesh_);
		btShapeHull* hull = new btShapeHull(&convexShape);
		btScalar margin = convexShape.getMargin();
		hull->buildHull(margin);

		btConvexHullShape* convexHull = new btConvexHullShape();
		for (int i = 0; i < hull->numVertices(); i++)
		{
			btVector3 point = hull->getVertexPointer()[i];
			convexHull->addPoint(point);
		}

		shape_ = convexHull;
		delete hull;
	}

	void CompoundCollider::generateShape()
	{
		btCompoundShape* tmpShape = new btCompoundShape();
		for (int i = 0; i < colliders_.size(); i++)
		{
			btTransform trans;
			trans.setFromOpenGLMatrix(glm::value_ptr(transforms_[i]));
			tmpShape->addChildShape(trans, colliders_[i]->getShape());
		}

		shape_ = tmpShape;
	}

	void CompoundCollider::addCollider(Collider* collider, glm::mat4 transform)
	{
		colliders_.emplace_back(collider);
		transforms_.push_back(transform);
	}
	
}