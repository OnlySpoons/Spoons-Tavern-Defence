#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "stb_image.h"

#include "Window.h"
#include "Shader.h"
#include "GameObject.h"
#include "Skybox.h"

namespace GameEngine {

	class Renderer
	{

	//Member Variables
	private:
		Window* _Window;
		Camera* _Camera;

		Shader _GeometryShader, _LightingShader, _LightsShader, _PostProcessShader;

		unsigned int _gBuffer, _gPosition, _gNormal, _gAlbedoSpec;

		std::vector<GameObject*> _GameObjects;

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

		//Functions to control the objects to render
		void addObject(GameObject* obj);
		void removeObject();
	};
}