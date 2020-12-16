#include "Entity.h"

namespace Spoonity {

	Entity::Entity(const ObjectData const& data, const std::string const& modelPath, const Shader const& shader)
		: GameObject(data, shader), _Model(Model(modelPath))
	{
		
	}

	void Entity::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model)
	{
		if (_IsEnabled)
		{
			_Shader.use();
			_Shader.setMat4("projection", projection);
			_Shader.setMat4("view", view);

			glm::vec3 lookPos = _Data.position + glm::vec3(_Data.direction.x, 0.0f, _Data.direction.z);

			model = glm::mat4(1.0f);
			model = glm::translate(model, _Data.position);
			model *= glm::lookAt(_Data.position, lookPos, Camera::_WorldUp);
			model = glm::scale(model, _Data.scale);

			_Model.draw(_Shader, &model);
		}
	}

	void Entity::update(float& deltaTime)
	{
	}
}