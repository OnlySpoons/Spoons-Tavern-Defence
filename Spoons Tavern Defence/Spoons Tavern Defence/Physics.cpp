#include "Physics.h"

namespace spty {

	btBroadphaseInterface* Physics::pBroadphase_ = nullptr;
	btCollisionConfiguration* Physics::pCollisionConfiguration_ = nullptr;
	btCollisionDispatcher* Physics::pDispatcher_ = nullptr;
	btConstraintSolver* Physics::pSolver_ = nullptr;
	btDynamicsWorld* Physics::pWorld_ = nullptr;

	float Physics::gravity_ = PhysicsConstants::GRAVITY;

	void Physics::init(float G)
	{
		gravity_ = PhysicsConstants::GRAVITY;

		// create the collision configuration
		pCollisionConfiguration_ = new btDefaultCollisionConfiguration();
		// create the dispatcher
		pDispatcher_ = new btCollisionDispatcher(pCollisionConfiguration_);
		// create the broadphase
		pBroadphase_ = new btDbvtBroadphase();
		// create the constraint solver
		pSolver_ = new btSequentialImpulseConstraintSolver();
		// create the world
		pWorld_ = new btDiscreteDynamicsWorld(pDispatcher_, pBroadphase_, pSolver_, pCollisionConfiguration_);
		setGravity(gravity_);
	}

	void Physics::cleanup()
	{
		delete pWorld_;
		delete pSolver_;
		delete pBroadphase_;
		delete pDispatcher_;
		delete pCollisionConfiguration_;
	}

	void Physics::Update(float& deltaTime, const Scene& scene)
	{
		pWorld_->stepSimulation(deltaTime);
		scene.physicsUpdate();
	}

	RayCallback Physics::Raycast(const glm::vec3& start, const glm::vec3& end)
	{
		RayCallback rayCallback(glmVec3TobtVector3(start), glmVec3TobtVector3(end));

		// Perform Raycast
		pWorld_->rayTest(glmVec3TobtVector3(start), glmVec3TobtVector3(end), rayCallback);

		return rayCallback;
	}

	void Physics::addBulletBody(btRigidBody* r)
	{
		pWorld_->addRigidBody(r);
	}

	void Physics::removeBulletBody(btRigidBody* r)
	{
		pWorld_->removeRigidBody(r);
	}

	void Physics::setGravity(float g)
	{
		gravity_ = g;
		pWorld_->setGravity(btVector3(0, -gravity_, 0));
	}

	void Physics::setDebugDrawer(BulletDebugDrawer* debugDrawer)
	{
		pWorld_->setDebugDrawer(debugDrawer);
	}

	void Physics::debugDraw()
	{
		pWorld_->debugDrawWorld();
	}
}