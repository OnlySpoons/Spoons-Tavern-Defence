#include "Entity.h"
#include <iostream>

namespace Spoonity {

	Entity::Entity(const Transform& data,
		const std::string& modelPath)
		: GameObject(data), _model(Model(modelPath))
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
}