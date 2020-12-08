#pragma once
#include "GameObject.h"

namespace GameEngine {

	class Skybox : public GameObject
	{
	//Variables
	private:
		//Inherited Variables
		//_Data - position, direction, and rotation data
		//_GeometryShader - shader used to render the object

		//Skybox render data
		std::vector<std::string> _TextureFaces;
		unsigned int _VAO, _VBO, _TextureCube;


	//Functions
	public:

		//Constructors
		Skybox(ObjectData data, std::vector<std::string> faces, Shader shader);

		void Draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model) override;

		void Update() override;

	private:

		unsigned int InitTextureCube() const;

		void genBuffers();

	};
}