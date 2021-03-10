#include "Physics.h"
#include "RigidBody.h"

namespace Spoonity {

	Physics::Physics(float G) { Init(PhysicsConstants.GRAVITY); }

	void Physics::Init(float g)
	{
		gravity = PhysicsConstants.GRAVITY;

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
		setGravity(g);
	}

	Physics::~Physics()
	{
		delete m_pWorld;
		delete m_pSolver;
		delete m_pBroadphase;
		delete m_pDispatcher;
		delete m_pCollisionConfiguration;
	}

	void Physics::AddObject(Entity& obj)
	{
		//TODO: add check to make sure object has rigid body before adding to vector
		physicsObjects.push_back(&obj);
	}

	void Physics::addBulletBody(btRigidBody* r)
	{
		m_pWorld->addRigidBody(r);
	}

	void Physics::setGravity(float g)
	{
		gravity = g;

		m_pWorld->setGravity(btVector3(0, -gravity, 0));
	}

	float Physics::getGravity()
	{
		return gravity;
	}

	void Physics::Update(float& deltaTime)
	{
		m_pWorld->stepSimulation(deltaTime);

		//Update all game objects transforms to match physics transforms
		for (int i = 0; i < physicsObjects.size(); i++)
		{
			//TODO: need to update every single rigidBody in vector list by offset based on rb's offset from entity coords in local space
			for (int j = 0; j < physicsObjects[j]->_rigidBodies.size(); j++)
			{
				//TEMP: replace with transform
				physicsObjects[i]->_Data.position = physicsObjects[i]->_rigidBodies[j]->getBulletPosition();

				physicsObjects[i]->_Data.angle.x = physicsObjects[i]->_rigidBodies[j]->getBulletRotation().x;
				physicsObjects[i]->_Data.angle.y = physicsObjects[i]->_rigidBodies[j]->getBulletRotation().y;
			}
		}
	}

}