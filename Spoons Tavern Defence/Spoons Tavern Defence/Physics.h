#pragma once
#include "bullet/btBulletDynamicsCommon.h"

#include "PhysicsConstants.h"
#include "Scene.h"
#include "BulletDebugDrawer.h"

#include <vector>

namespace spty
{
	class Physics 
	{
	public:
		static void init(float g = PhysicsConstants::GRAVITY);

		static void cleanup();

		static void setGravity(float g);
		static float getGravity();
		static glm::vec3 getGravityVector();

		static void Update(float& deltaTime, const Scene& scene);

		//Helper functions
		static inline btVector3 glmVec3TobtVector3(const glm::vec3& vec) { return btVector3(vec.x, vec.y, vec.z); }
		static inline glm::vec3 btVector3ToglmVec3(const btVector3& vec) { return glm::vec3(vec.getX(), vec.getY(), vec.getZ()); }
		static inline btQuaternion asQuaternion(glm::vec3 rot) { return btQuaternion(rot.x, rot.y, rot.z); }

		static void addBulletBody(btRigidBody* r);

		static void setDebugDrawer(BulletDebugDrawer* debugDrawer);
		static void debugDraw();

		/*static inline btTransform TransformTobtTransform(Transform transform)
		{
			btTransform result;
			result.setRotation(asQuaternion(transform.getRotation()));
			result.setOrigin(glmVec3TobtVector3(transform.getPosition()));
		}*/

	private:
		//Core Bullet components
		static btBroadphaseInterface* m_pBroadphase;
		static btCollisionConfiguration* m_pCollisionConfiguration;
		static btCollisionDispatcher* m_pDispatcher;
		static btConstraintSolver* m_pSolver;
		static btDynamicsWorld* m_pWorld;
		
		static float _gravity;
	};
}