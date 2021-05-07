#include "PhysicsEntity.h"

spty::PhysicsEntity::PhysicsEntity(const Transform& data, Model* model, Collider* collider)
	: Entity(data, model), rigidBody_(transform_, collider ? collider : model_->getCompoundShape())
{
}

spty::PhysicsEntity::~PhysicsEntity()
{
}

void spty::PhysicsEntity::draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass)
{
	Entity::draw(shader, projection, view, model, pass);
}

void spty::PhysicsEntity::physicsUpdate()
{
	transform_.setPosition(rigidBody_.getBulletPosition());
	//transform_.setRotation( rigidBody_.getBulletRotation() );
}
