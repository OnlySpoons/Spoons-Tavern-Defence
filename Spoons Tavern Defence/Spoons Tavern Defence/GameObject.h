#pragma once
#include "Shader.h"
#include "Transform.h"
#include "PassType.h"

namespace spty {

	class GameObject
	{
	//Variables
	public:
		Transform _transform;
		bool _isEnabled;

	//Functions
	public:

		//Constructors
		GameObject() :_transform(Transform()), _isEnabled(false) {}

		GameObject(const Transform& data,
			const bool& enabled = false)
			: _transform(data), _isEnabled(enabled)
		{
		}

		//Destructor
		virtual ~GameObject() {}

		//Render the object
		virtual void draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass) = 0;

		//Update the object
		virtual void update(float& deltaTime) = 0;

		virtual void physicsUpdate() = 0;

		//Enable object to be rendered and process physics
		void enable()
		{
			_isEnabled = true;
		}

		//Disable object from being rendered and processing physics
		void disable()
		{
			_isEnabled = false;
		}
	};
}