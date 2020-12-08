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

		bool _IsEnabled;

	//Functions
	public:

		//Constructors
		GameObject(const ObjectData &data, const Shader &shader, bool enabled)
			: _Data(data), _Shader(shader), _IsEnabled(enabled)
		{
		}

		//Render the object
		virtual void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model) = 0;

		//Update the object
		virtual void update(float &deltaTime) = 0;

		//Enable object to be rendered and process physics
		void enable()
		{
			_IsEnabled = true;
		}

		//Disable object from being rendered and processing physics
		void disable()
		{
			_IsEnabled = false;
		}
	};
}