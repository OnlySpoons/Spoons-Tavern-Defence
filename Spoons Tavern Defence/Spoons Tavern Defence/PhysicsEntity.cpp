#include "PhysicsEntity.h"

spty::PhysicsEntity::PhysicsEntity(const Transform& data,
	const std::string& modelPath, Collider* collider)
	: Entity(data, modelPath),
	_rigidBody(_transform, 
		collider != nullptr ? collider : _model.getCompoundShape()
	)
{
}

void spty::PhysicsEntity::update(float& deltaTime)
{
}

void spty::PhysicsEntity::physicsUpdate()
{
	_transform.setPosition(_rigidBody.getBulletPosition());
	//_transform.setRotation( _rigidBody.getBulletRotation() );
}
