#include "Collider.h"

namespace spty {

	//Physics Material Constructors
	PhysicsMaterial::PhysicsMaterial(float f, float b)
	{
		_friction = f;
		_bounciness = b;
	}
	PhysicsMaterial::PhysicsMaterial() 
	{
		_friction = PhysicsConstants::FRICTION;
		_bounciness = 0.0f;
	}

	//Box Collider Constructors
	BoxCollider::BoxCollider()
	{ 
		_size = glm::vec3(1.0f, 1.0f, 1.0f);
		generateShape();
	}
	BoxCollider::BoxCollider(glm::vec3 s)
	{ 
		_size = s;
		generateShape();
	}

	//Sphere Collider Constructors
	SphereCollider::SphereCollider() 
	{ 
		_radius = 1.0f;
		generateShape();
	}
	SphereCollider::SphereCollider(float r)
	{ 
		_radius = r;
		generateShape();
	}

	CapsuleCollider::CapsuleCollider()
	{
		_radius = 0.5f;
		_height = 1.0f;
		generateShape();
	}
	CapsuleCollider::CapsuleCollider(float r, float h)
	{
		_radius = r;
		_height = h;
		generateShape();
	}

	//Mesh Collider Constuctors
	MeshCollider::MeshCollider()
	{
		_mesh = new btTriangleMesh();
		generateShape();
	}
	MeshCollider::MeshCollider(const btTriangleMesh& m)
	{
		_mesh = m;
		generateShape();
	}

	//Compound Collider Constructors
	CompoundCollider::CompoundCollider()
	{
		_colliders = {};
		_transforms = {};
		generateShape();
	}
	CompoundCollider::CompoundCollider(const std::vector<Collider*>& colliders, const std::vector<glm::mat4>& transforms)
	{
		_colliders = colliders;
		_transforms = transforms;
		generateShape();
	}

	//Generate shape functions
	void BoxCollider::generateShape() { _shape = new btBoxShape(Physics::glmVec3TobtVector3(_size)); }
	void SphereCollider::generateShape() { _shape = new btSphereShape(_radius); }
	void CapsuleCollider::generateShape() { _shape = new btCapsuleShape(_radius, _height); }

	void MeshCollider::generateShape()
	{
		/*btTriangleMesh trimesh = btTriangleMesh();
		trimesh.addTriangle(btVector3(1, 0, 0), btVector3(0, 1, 0), btVector3(0, 0, 0));
		trimesh.addTriangle(btVector3(1, 0, 0), btVector3(0, 1, 0), btVector3(0.5, 0.5, 0.5));
		trimesh.addTriangle(btVector3(0, 0, 0), btVector3(0, 1, 0), btVector3(0.5, 0.5, 0.5));
		trimesh.addTriangle(btVector3(1, 0, 0), btVector3(0, 0, 0), btVector3(0.5, 0.5, 0.5));*/

		btConvexTriangleMeshShape convexShape = btConvexTriangleMeshShape(&_mesh);
		btShapeHull* hull = new btShapeHull(&convexShape);
		int margin = convexShape.getMargin();
		hull->buildHull(margin);
		/*convexShape->setUserPointer(hull);*/

		btConvexHullShape* convexHull = new btConvexHullShape();
		for (int i = 0; i < hull->numVertices(); i++)
		{
			btVector3 point = hull->getVertexPointer()[i];
			convexHull->addPoint(point);
		}

		_shape = convexHull;
	}

	void CompoundCollider::generateShape()
	{
		btCompoundShape* tmpShape = new btCompoundShape();
		for (int i = 0; i < _colliders.size(); i++)
		{
			btTransform trans;
			trans.setFromOpenGLMatrix(glm::value_ptr(_transforms[i]));
			tmpShape->addChildShape(trans, _colliders[i]->getShape());
		}

		_shape = tmpShape;
	}

	//Getters, Setters and Adders
	void BoxCollider::setSize(glm::vec3 s) { _size = s; generateShape();  }
	glm::vec3 BoxCollider::getSize() { return _size; }

	void SphereCollider::setRadius(float r) { _radius = r; generateShape(); }
	float SphereCollider::getRadius() { return _radius; }

	void CompoundCollider::addCollider(Collider* collider, glm::mat4 transform)
	{
		_colliders.emplace_back(collider);
		_transforms.push_back(transform);
	}
	
}