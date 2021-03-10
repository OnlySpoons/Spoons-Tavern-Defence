#include "Collider.h"

namespace Spoonity {

	PhysicsMaterial::PhysicsMaterial(float f, float b) 
	{ 
		friction = f; 
		bounciness = b; 
	}
	PhysicsMaterial::PhysicsMaterial() 
	{ 
		friction = PhysicsConstants.FRICTION; 
		bounciness = PhysicsConstants.BOUNCE; 
	}

	//--------------------------DELETED FUNCTION ERROR--------------------------
	BoxCollider::BoxCollider()
	{ 
		size = PhysicsConstants.CUBE_SIZE; 
		centre = PhysicsConstants.CENTRE; 
		generateShape(); 
	}
	BoxCollider::BoxCollider(glm::vec3 s, glm::vec3 c)
	{ 
		size = s; 
		centre = c; 
		generateShape(); 
	}

	SphereCollider::SphereCollider() 
	{ 
		radius = PhysicsConstants.RADIUS; 
		centre = PhysicsConstants.CENTRE; 
		generateShape(); 
	}
	SphereCollider::SphereCollider(float r, glm::vec3 c) 
	{ 
		radius = r; 
		centre = c; 
		generateShape(); 
	}
	//--------------------------DELETED FUNCTION ERROR--------------------------

	void BoxCollider::generateShape() { shape = new btBoxShape(Physics::convertVector(size)); }
	void SphereCollider::generateShape() { shape = new btSphereShape(radius); }

	glm::vec3 Collider::getCentre() { return centre; }
	glm::vec3 BoxCollider::getSize() { return size; }
	void SphereCollider::setRadius(float r) { radius = r; }
	float SphereCollider::getRadius() { return radius; }

	void BoxCollider::setSize(glm::vec3 s) { size = s; generateShape(); }
	void Collider::setCentre(glm::vec3 c) { centre = c; } //Not working
}