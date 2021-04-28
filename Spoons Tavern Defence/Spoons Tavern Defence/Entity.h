#pragma once
#include "GameObject.h"
#include "Camera.h"
#include "Model.h"

namespace spty {

	class Entity : public GameObject
	{
		//Variables
	protected:
		//Entities control their own model
		Model _model;

		//Functions
	public:

		//Constructors
		Entity() {}

		Entity(const Transform& data,
			const std::string& modelPath = ""
		);

		virtual ~Entity() {}

		//Render the object
		virtual void draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass) override;

		//Unused by skybox
		virtual void update(float& deltaTime) override;

		virtual void physicsUpdate() override {}
	};
}