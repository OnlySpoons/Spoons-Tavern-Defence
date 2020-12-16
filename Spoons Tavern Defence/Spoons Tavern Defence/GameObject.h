#pragma once
#include "Shader.h"

namespace Spoonity {

	struct ObjectData {
		float speed;
		glm::vec3 position;
		glm::vec3 direction;
		glm::vec3 scale;

		ObjectData(const glm::vec3& pos = glm::vec3(0.0f),
				   const glm::vec3& dir = glm::vec3(1.0f, 0.0f, 0.0f),
				   const glm::vec3& sca = glm::vec3(1.0f),
				   const float spd = 0.0f)
			: position(pos), direction(dir), scale(sca), speed(spd) {
		}
	};

	class GameObject
	{
	//Variables
	protected:
		bool _IsEnabled;

		ObjectData _Data;

		Shader _Shader;

	//Functions
	public:

		//Constructor
		GameObject(const ObjectData const &data,
				   const Shader const &shader,
				   const bool &enabled = false)
			: _Data(data), _Shader(shader), _IsEnabled(enabled) {
		}

		//Destructor
		virtual ~GameObject() {}

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