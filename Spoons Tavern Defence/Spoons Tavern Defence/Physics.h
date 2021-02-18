#pragma once
#include "bullet/btBulletDynamicsCommon.h"
#include "GameObject.h"

namespace Spoonity
{
	class Physics 
	{
	private:
		//Core Bullet components
		btBroadphaseInterface* m_pBroadphase;
		btCollisionConfiguration* m_pCollisionConfiguration;
		btCollisionDispatcher* m_pDispatcher;
		btConstraintSolver* m_pSolver;
		btDynamicsWorld* m_pWorld;

	public:
		//Default constructor
		Physics();

		//Destructor
		~Physics();

		void AddObject(const GameObject& obj);
	};
}