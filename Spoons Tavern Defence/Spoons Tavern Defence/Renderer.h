#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "stb_image.h"

#include "Window.h"
#include "Shader.h"

#include "Model.h"

namespace GameEngine {

	class Renderer
	{

	//Member Variables
	private:
		Window* _Window;
		Camera* _Camera;

		Shader _GeometryShader, _LightingShader, _LightsShader, _PostProcessShader, /*temp*/_SkyboxShader;

		unsigned int _gBuffer, _gPosition, _gNormal, _gAlbedoSpec, /* temp */_SkyboxTexture;

		//TODO: lighting class/rename
		std::vector<glm::vec3> lightPositions;
		std::vector<glm::vec3> lightColors;

		std::vector<glm::vec3> objectPositions;

		Model _model;

	//Functions
	public:

		//Constructors
		Renderer();

		Renderer(Window* window, Camera* camera);

		//Function for configuring buffers
		void genBuffers();

		//Render the scene
		void renderScene();
	};
}