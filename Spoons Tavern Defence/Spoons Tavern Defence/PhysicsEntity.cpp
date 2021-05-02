#include "PhysicsEntity.h"

spty::PhysicsEntity::PhysicsEntity(const Transform& data,
	Model* model, Collider* collider)
	: Entity(data, model),
	_rigidBody(_transform, 
		collider != nullptr ? collider : _model->getCompoundShape()
	)
{
}

void spty::PhysicsEntity::draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass)
{
	Entity::draw(shader, projection, view, model, pass);
}

void spty::PhysicsEntity::physicsUpdate()
{
	_transform.setPosition(_rigidBody.getBulletPosition());
	//_transform.setRotation( _rigidBody.getBulletRotation() );
}
