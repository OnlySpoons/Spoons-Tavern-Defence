#include "Entity.h"
#include <iostream>

namespace Spoonity {

	Entity::Entity(const ObjectData& data,
		const std::string& modelPath)
		: GameObject(data), _model(Model(modelPath))
	{

	}

	void Entity::draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model)
	{
		if (_isEnabled)
		{
			shader.use();
			shader.setMat4("projection", projection);
			shader.setMat4("view", view);

			glm::vec3 lookPos = _data.position + _data.front;

			model = glm::mat4(1.0f);
			model = glm::translate(model, _data.position);
			model = glm::rotate(model, glm::radians(_data.angle.x), _data.front);
			model = glm::rotate(model, glm::radians(_data.angle.y), _data.up);
			model = glm::scale(model, _data.scale);

			_model.draw(shader, model);
		}
	}

	void Entity::update(float& deltaTime)
	{
	}
}