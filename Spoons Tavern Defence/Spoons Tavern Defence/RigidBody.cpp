#include "RigidBody.h"

namespace Spoonity {

	void Spoonity::RigidBody::init()
	{
		//Aborts if object doesn't have a bullet collider
		if (collider == nullptr)
			return; //TODO: add log message

		btDefaultMotionState* motion = new btDefaultMotionState(btTransform(btQuaternion(/*xyz rotation*/), /*position*/)); //TODO: fill in with Transform data when done
		btVector3 initInertia = Physics::convertVector(inertia);
		collider->shape->calculateLocalInertia(mass, initInertia);

		//Construct
		btRigidBody::btRigidBodyConstructionInfo construction(mass, motion, collider->shape, Physics::convertVector(inertia));
		body = new btRigidBody(construction);

		//Add to the bullet world
		Physics::addBulletBody(body);
	}

	void Spoonity::RigidBody::setMass(float m)
	{
		mass = m;
	}

	void Spoonity::RigidBody::setForce(glm::vec3 f)
	{
		inertia = f;
	}

	void Spoonity::RigidBody::setKinematic(bool val)
	{
		kinematic = val; 
		if (kinematic == true)
			setMass(0);
	}

	btTransform Spoonity::RigidBody::getWorldTransform()
	{
		btTransform result;
		body->getMotionState()->getWorldTransform(result);
		return result;
	}

	glm::vec3 Spoonity::RigidBody::getBulletPosition()
	{
		return Physics::convertVectorBack(getWorldTransform().getOrigin());
	}

	//TODO
	glm::vec3 Spoonity::RigidBody::getBulletRotation()
	{
		return glm::vec3(0); //TEMP
	}

}