#include "Glasses.h"

namespace GameEngine {

	Glasses::Glasses(const ObjectData& const data, const std::string& const modelPath, const Shader& const shader, const Shader& const postProcessShader)
		: Entity(data, modelPath, shader), _PostProcessShader(postProcessShader)
	{
	}

	void Glasses::update(float& deltaTime)
	{
		//TODO: bobbing and rotating code
	}
}