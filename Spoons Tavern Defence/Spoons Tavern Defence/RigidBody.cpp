#include "RigidBody.h"

namespace spty {

	RigidBody::RigidBody(const Transform& transform, Collider* col)
		: _collider(col)
	{
		btDefaultMotionState* motion = new btDefaultMotionState(
			btTransform(
				btQuaternion(
					transform.getPitch(),
					transform.getYaw(),
					transform.getRoll()
				),
				Physics::glmVec3TobtVector3(transform.getPosition())
			)
		);

		_collider->getShape()->setLocalScaling( Physics::glmVec3TobtVector3( transform.getScale() ) );

		//Construct
		btRigidBody::btRigidBodyConstructionInfo construction(_mass, motion, _collider->_shape, Physics::glmVec3TobtVector3(_inertia));
		_body = new btRigidBody(construction);

		_body->setActivationState(4);

		//TODO: Make this an event
		//Add to the bullet world
		Physics::addBulletBody(_body);
	}

	RigidBody::~RigidBody()
	{
		delete _collider;
		delete _body;
	}

	void spty::RigidBody::setMass(float m)
	{
		_mass = m;
		_body->setMassProps(_mass, Physics::glmVec3TobtVector3(_inertia));
	}

	void spty::RigidBody::setForce(glm::vec3 f)
	{
		_inertia = f;
		_body->setMassProps(_mass, Physics::glmVec3TobtVector3(_inertia));
	}

	void spty::RigidBody::setKinematic(bool val)
	{
		_kinematic = val; 
		if (_kinematic)
			setMass(0);
		else
			setMass(1);
	}

	void RigidBody::move(glm::vec3 direction)
	{
		direction.y += _body->getLinearVelocity().y();
		_body->setLinearVelocity(Physics::glmVec3TobtVector3(direction));
	}

	btTransform spty::RigidBody::getWorldTransform()
	{
		btTransform result;
		_body->getMotionState()->getWorldTransform(result);
		return result;
	}

	glm::vec3 spty::RigidBody::getBulletPosition()
	{
		return Physics::btVector3ToglmVec3(getWorldTransform().getOrigin());
	}

	glm::vec3 spty::RigidBody::getBulletRotation()
	{
		float x, y, z;
		getWorldTransform().getRotation().getEulerZYX(z, y, x);
		return glm::vec3(x, y, z);
	}

	glm::vec3 RigidBody::getBulletInertia()
	{
		return _inertia;
	}

	void RigidBody::calculateLocalInertia()
	{
		btVector3 localInertia;
		_collider->_shape->calculateLocalInertia(_mass, localInertia);
		_inertia = Physics::btVector3ToglmVec3(localInertia);
	}
}