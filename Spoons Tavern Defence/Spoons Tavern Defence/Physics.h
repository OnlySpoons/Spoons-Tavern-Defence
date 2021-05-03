#pragma once
#include "bullet/btBulletDynamicsCommon.h"

#include "PhysicsConstants.h"
#include "Scene.h"
#include "BulletDebugDrawer.h"

#include <vector>

namespace spty
{
	using RayCallback = btCollisionWorld::ClosestRayResultCallback;

	class Physics 
	{
		//Core Bullet components
		static btBroadphaseInterface* m_pBroadphase;
		static btCollisionConfiguration* m_pCollisionConfiguration;
		static btCollisionDispatcher* m_pDispatcher;
		static btConstraintSolver* m_pSolver;
		static btDynamicsWorld* m_pWorld;

		static float _gravity;

	public:
		static void init(float g = PhysicsConstants::GRAVITY);

		static void cleanup();

		//Parameter functions
		static void setGravity(float g);
		static float getGravity();
		static glm::vec3 getGravityVector();

		static void Update(float& deltaTime, const Scene& scene);

		static RayCallback Raycast(const glm::vec3& start, const glm::vec3& end);

		//Helper functions
		static inline btVector3 glmVec3TobtVector3(const glm::vec3& vec) { return btVector3(vec.x, vec.y, vec.z); }
		static inline glm::vec3 btVector3ToglmVec3(const btVector3& vec) { return glm::vec3(vec.getX(), vec.getY(), vec.getZ()); }
		static inline btQuaternion asQuaternion(glm::vec3 rot) { return btQuaternion(rot.x, rot.y, rot.z); }

		static void addBulletBody(btRigidBody* r);
		static void removeBulletBody(btRigidBody* r);

		static void setDebugDrawer(BulletDebugDrawer* debugDrawer);
		static void debugDraw();
	};
}