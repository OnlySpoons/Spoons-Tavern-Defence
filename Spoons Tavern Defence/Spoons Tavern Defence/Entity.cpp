#include "Entity.h"

namespace spty {

	Entity::Entity(const Transform& data,
		Model* model)
		: GameObject(data),
		model_(model != nullptr ? model : new Model())
	{
	}

	Entity::~Entity()
	{
		model_ = nullptr;
	}

	void Entity::draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass)
	{
		if (!isEnabled_) return;

		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		model = transform_.getMatrix();

		model_->draw(shader, model);
	}
}