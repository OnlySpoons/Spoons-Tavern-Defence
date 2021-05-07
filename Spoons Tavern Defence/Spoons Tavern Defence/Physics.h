#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <vector>

#include <bullet/btBulletDynamicsCommon.h>

#include "PhysicsConstants.h"
#include "Scene.h"
#include "BulletDebugDrawer.h"


namespace spty
{
	using RayCallback = btCollisionWorld::ClosestRayResultCallback;

	class Physics
	{
	//Variables
	private:
		//Core Bullet components
		static btBroadphaseInterface* pBroadphase_;
		static btCollisionConfiguration* pCollisionConfiguration_;
		static btCollisionDispatcher* pDispatcher_;
		static btConstraintSolver* pSolver_;
		static btDynamicsWorld* pWorld_;

		static float gravity_;

	//Functions
	public:
		static void init(float g = PhysicsConstants::GRAVITY);

		static void cleanup();

		static void Update(float& deltaTime, const Scene& scene);

		static RayCallback Raycast(const glm::vec3& start, const glm::vec3& end);

		static inline btVector3 glmVec3TobtVector3(const glm::vec3& vec) { return btVector3(vec.x, vec.y, vec.z); }
		static inline glm::vec3 btVector3ToglmVec3(const btVector3& vec) { return glm::vec3(vec.getX(), vec.getY(), vec.getZ()); }
		static inline btQuaternion asQuaternion(glm::vec3 rot) { return btQuaternion(rot.x, rot.y, rot.z); }

		static void addBulletBody(btRigidBody* r);
		static void removeBulletBody(btRigidBody* r);

		static void setGravity(float g);
		static float getGravity() { return gravity_; }
		static glm::vec3 getGravityVector() { return glm::vec3(0.0f, -gravity_, 0.0f); }

		static void setDebugDrawer(BulletDebugDrawer* debugDrawer);
		static void debugDraw();
	};
}