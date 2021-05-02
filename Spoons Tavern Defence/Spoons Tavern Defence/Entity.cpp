#include "Entity.h"

namespace spty {

	Entity::Entity(const Transform& data,
		Model* model)
		: GameObject(data),
		_model(model != nullptr ? model : new Model())
	{
	}

	Entity::~Entity()
	{
		_model = nullptr;
	}

	void Entity::draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass)
	{
		if (_isEnabled)
		{
			shader.use();
			shader.setMat4("projection", projection);
			shader.setMat4("view", view);

			model = _transform.getMatrix();

			_model->draw(shader, model);
		}
	}
}