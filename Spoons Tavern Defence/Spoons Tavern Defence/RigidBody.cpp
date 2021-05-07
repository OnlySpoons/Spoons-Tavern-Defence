#include "RigidBody.h"

namespace spty {

	RigidBody::RigidBody(const Transform& transform, Collider* col)
		: collider_(col)
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

		collider_->getShape()->setLocalScaling( Physics::glmVec3TobtVector3( transform.getScale() ) );

		//Construct
		btRigidBody::btRigidBodyConstructionInfo construction(mass_, motion, collider_->shape_, Physics::glmVec3TobtVector3(inertia_));
		body_ = new btRigidBody(construction);

		body_->setActivationState(4);

		//Add to the bullet world
		Physics::addBulletBody(body_);
		body_->setFriction(0.2f);
	}

	RigidBody::~RigidBody()
	{
		delete body_->getMotionState();
		delete collider_;

		Physics::removeBulletBody(body_);
		delete body_;
	}

	void spty::RigidBody::setMass(float m)
	{
		mass_ = m;
		body_->setMassProps(mass_, Physics::glmVec3TobtVector3(inertia_));
	}

	void spty::RigidBody::setForce(glm::vec3 f)
	{
		inertia_ = f;
		body_->setMassProps(mass_, Physics::glmVec3TobtVector3(inertia_));
	}

	void spty::RigidBody::setKinematic(bool val)
	{
		kinematic_ = val; 
		if (kinematic_)
			setMass(0);
		else
			setMass(1);
	}

	void RigidBody::setLinearDamping(float val)
	{
		body_->setDamping(val, body_->getAngularDamping());
	}

	void RigidBody::move(glm::vec3 direction)
	{
		direction.y += body_->getLinearVelocity().y();
		body_->setLinearVelocity(Physics::glmVec3TobtVector3(direction));
	}

	btTransform spty::RigidBody::getWorldTransform()
	{
		btTransform result;
		body_->getMotionState()->getWorldTransform(result);
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
		return inertia_;
	}

	void RigidBody::calculateLocalInertia()
	{
		btVector3 localInertia;
		collider_->shape_->calculateLocalInertia(mass_, localInertia);
		inertia_ = Physics::btVector3ToglmVec3(localInertia);
	}

	void RigidBody::disableGravity()
	{
		body_->setGravity({ 0.0f, 0.0f, 0.0f });
	}

	void RigidBody::enableGravity()
	{
		body_->setGravity( Physics::glmVec3TobtVector3( Physics::getGravityVector() ) );
	}
}