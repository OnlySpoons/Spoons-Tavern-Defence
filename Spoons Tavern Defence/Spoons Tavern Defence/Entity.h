#pragma once
#include "GameObject.h"
#include "Model.h"

namespace GameEngine {

	class Entity : public GameObject
	{
	//Variables
	private:
		//Entities control their own model
		Model _Model;

	//Functions
	public:

		//Constructor
		Entity(const ObjectData const &data, const std::string const &modelPath, const Shader const &shader);

		//Render the object
		virtual void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model) override;

		//Unused by skybox
		virtual void update(float& deltaTime) override;

	};
}