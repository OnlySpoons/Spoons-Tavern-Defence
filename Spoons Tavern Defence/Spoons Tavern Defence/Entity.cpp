#include "Entity.h"

namespace spty {

	Entity::Entity(const Transform& data,
		const std::string& modelPath)
		: GameObject(data),
		_model(modelPath == "" ? Model() : Model(modelPath)),
		_rigidBody(_transform, _model.getCompoundShape())
	{
	}

	void Entity::draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass)
	{
		if (_isEnabled)
		{
			shader.use();
			shader.setMat4("projection", projection);
			shader.setMat4("view", view);

			model = _transform.getMatrix();

			_model.draw(shader, model);
		}
	}

	void Entity::update(float& deltaTime)
	{
	}

	void Entity::physicsUpdate()
	{
		_transform.setPosition( _rigidBody.getBulletPosition() );
		//_transform.setRotation( _rigidBody.getBulletRotation() );
	}
}