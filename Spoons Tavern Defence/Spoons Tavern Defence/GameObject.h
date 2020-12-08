#pragma once
#include "Shader.h"
#include "Model.h"

struct ObjectData {
	glm::vec3 position;
	glm::vec3 direction;
	glm::quat rotation;

	ObjectData(const glm::vec3& pos = glm::vec3(0.0f), const glm::vec3& dir = glm::vec3(0.0f, 1.0f, 0.0f), const glm::quat& rot = glm::quat(0.0f, 1.0f, 0.0f, 0.0f))
		: position(pos), direction(dir), rotation(rot)
	{
	}
};

namespace GameEngine {

	class GameObject
	{
	//Variables
	protected:
		ObjectData _Data;

		Shader _Shader;

	//Functions
	public:

		//Constructors
		GameObject(const ObjectData &data, const Shader &shader)
			: _Data(data), _Shader(shader)
		{
		}

		//Draw the object
		virtual void Draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model) = 0;

		//Update the object
		virtual void Update() = 0;
	};
}