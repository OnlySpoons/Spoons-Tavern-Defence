#include "Physics.h"

namespace spty {

	btBroadphaseInterface* Physics::m_pBroadphase = nullptr;
	btCollisionConfiguration* Physics::m_pCollisionConfiguration = nullptr;
	btCollisionDispatcher* Physics::m_pDispatcher = nullptr;
	btConstraintSolver* Physics::m_pSolver = nullptr;
	btDynamicsWorld* Physics::m_pWorld = nullptr;

	float Physics::_gravity = PhysicsConstants::GRAVITY;

	void Physics::init(float G)
	{
		_gravity = PhysicsConstants::GRAVITY;


		// create the collision configuration
		m_pCollisionConfiguration = new btDefaultCollisionConfiguration();
		// create the dispatcher
		m_pDispatcher = new btCollisionDispatcher(m_pCollisionConfiguration);
		// create the broadphase
		m_pBroadphase = new btDbvtBroadphase();
		// create the constraint solver
		m_pSolver = new btSequentialImpulseConstraintSolver();
		// create the world
		m_pWorld = new btDiscreteDynamicsWorld(m_pDispatcher, m_pBroadphase, m_pSolver, m_pCollisionConfiguration);
		setGravity(_gravity);
	}

	void Physics::cleanup()
	{
		delete m_pWorld;
		delete m_pSolver;
		delete m_pBroadphase;
		delete m_pDispatcher;
		delete m_pCollisionConfiguration;
	}

	void Physics::addBulletBody(btRigidBody* r)
	{
		m_pWorld->addRigidBody(r);
	}

	void Physics::setDebugDrawer(BulletDebugDrawer* debugDrawer)
	{
		m_pWorld->setDebugDrawer(debugDrawer);
	}

	void Physics::debugDraw()
	{

		m_pWorld->debugDrawWorld();
	}

	void Physics::setGravity(float g)
	{
		_gravity = g;

		m_pWorld->setGravity(btVector3(0, -_gravity, 0));
	}

	float Physics::getGravity()
	{
		return _gravity;
	}

	glm::vec3 Physics::getGravityVector()
	{
		return glm::vec3(0.0f, -_gravity, 0.0f);
	}

	void Physics::Update(float& deltaTime, const Scene& scene)
	{
		m_pWorld->stepSimulation(deltaTime);

		scene.physics();
	}

	bool Physics::Raycast(const glm::vec3& start, glm::vec3& end, glm::vec3& normal, const btCollisionObject* object)
	{
		btCollisionWorld::ClosestRayResultCallback RayCallback(glmVec3TobtVector3(start), glmVec3TobtVector3(end));

		// Perform Raycast
		m_pWorld->rayTest(glmVec3TobtVector3(start), glmVec3TobtVector3(end), RayCallback);
		if (RayCallback.hasHit())
		{
			end = btVector3ToglmVec3(RayCallback.m_hitPointWorld);
			normal = btVector3ToglmVec3(RayCallback.m_hitNormalWorld);
			object = RayCallback.m_collisionObject;
			return true;
		}

		return false;
	}

}