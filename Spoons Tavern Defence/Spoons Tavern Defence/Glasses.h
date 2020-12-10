#pragma once

#include "Entity.h"
#include "Renderer.h"

namespace GameEngine {

	class Glasses : public Entity
	{
	//Variables
	public:

		Shader _PostProcessShader;

	//Functions
	public:

		//Constructor
		Glasses(const ObjectData& const data, const std::string& const modelPath, const Shader& const shader, const Shader& const postProcessShader);

		void update(float& deltaTime) override;
	};
}