#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "stb_image.h"

#include "Window.h"
#include "Shader.h"
#include "Scene.h"

#include "GameObject.h"
#include "Skybox.h"

namespace GameEngine {

	class Renderer
	{

	//Variables
	public:
		Shader _PostProcessShader;

		Scene* _CurrentScene;

	private:
		Window* _Window;
		Camera* _Camera;

		Shader _LightingShader, _LightsShader;

		unsigned int _gBuffer, _gPosition, _gNormal, _gAlbedoSpec;

		unsigned int quadVAO, quadVBO;

		//TODO: lighting class/rename
		std::vector<glm::vec3> lightPositions;
		std::vector<glm::vec3> lightColors;

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