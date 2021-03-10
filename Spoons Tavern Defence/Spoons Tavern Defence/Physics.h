#pragma once
#include "bullet/btBulletDynamicsCommon.h"

#include "PhysicsConstants.h"
#include "Entity.h"

#include <vector>

namespace Spoonity
{
	class Physics 
	{
		friend class GameObject;
		friend class RigidBody;
		friend class BoxCollider;
		friend class Collider;

	public:
		Physics(float g = PhysicsConstants.GRAVITY);
		~Physics();

		void setGravity(float g);
		float getGravity();

		void Update(float& deltaTime);


	protected:
		//Core Bullet components
		btBroadphaseInterface* m_pBroadphase;
		btCollisionConfiguration* m_pCollisionConfiguration;
		btCollisionDispatcher* m_pDispatcher;
		btConstraintSolver* m_pSolver;
		static btDynamicsWorld* m_pWorld;

		//Helper functions
		static inline btVector3 convertVector(glm::vec3 foo) { return btVector3(foo.x, foo.y, foo.z); }
		static inline glm::vec3 convertVectorBack(const btVector3& foo) { return glm::vec3(foo.getX(), foo.getY(), foo.getZ()); }

		void AddObject(Entity& obj);
		static void addBulletBody(btRigidBody* r);
	
	private:
		void Init(float g);

		std::vector<Entity*> physicsObjects;
		float gravity;
	};
}