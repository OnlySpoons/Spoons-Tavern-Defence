#pragma once
#include <vector>
#include <string>

#include "stb_image.h"

#include "GameObject.h"
#include "Shader.h"

namespace Spoonity {

	class Skybox : public GameObject
	{
		//Variables
	private:
		//Inherited Variables
		//_data - position, direction, and rotation data
		//_geometryShader - shader used to render the object

		Shader _Shader;

		//Skybox render data
		std::vector<std::string> _TextureFaces;
		unsigned int _VAO, _VBO, _CubeTexture;


		//Functions
	public:

		//Constructor
		Skybox(const ObjectData& data,
			const std::vector<std::string>& faces,
			const Shader& shader);

		//Destructor
		~Skybox();

		//Render the object
		void draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass) override;

		//Unused by skybox
		void update(float& deltaTime) override {}

	private:

		//Initialises the cube texture
		unsigned int InitCubeTexture() const;

		//Generates the buffers for rendering the skybox
		void genBuffers();
	};
}