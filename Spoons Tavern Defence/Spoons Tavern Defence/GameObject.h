#pragma once
#include <string>

#include "Shader.h"
#include "Model.h"

struct ObjectData {
	glm::vec3 position;
	glm::vec3 direction;
	glm::quat rotation;
};

namespace GameEngine {

	class GameObject
	{
	//Variables
	protected:
		ObjectData _Data;

	//Functions
	public:

		//Constructor
		//GameObject(ObjectData &data, std::string const &&modelPath, std::string const &&geometryShader = "");

		//Draw the object
		virtual void Draw() const = 0;

		//Update the object
		virtual void Update() = 0;
	};
}