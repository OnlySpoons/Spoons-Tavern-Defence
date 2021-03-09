#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "stb_image.h"

#include "Shader.h"

#include "Scene.h"
#include "Camera.h"

#include "GameObject.h"
#include "Skybox.h"

namespace Spoonity {

	struct RenderData {
		glm::vec3 cameraPos;

		glm::mat4 projection;
		glm::mat4 view;
		glm::mat4 model;

		glm::mat4 lightProjection;
		glm::mat4 lightView;
		glm::mat4 lightSpaceMatrix;
	};

	class Renderer
	{

		//Variables
	public:
		Shader _postProcessShader;

		Skybox* _skybox;

	private:

		Shader _depthShader, _geometryShader, _lightingShader, _debugDepthShader;

		const unsigned int SHADOW_WIDTH = 8192, SHADOW_HEIGHT = 8192;

		unsigned int _windowWidth, _windowHeight;

		unsigned int _depthMapFBO, _depthMap;

		unsigned int _gBuffer, _gPosition, _gNormal, _gAlbedoSpec;

		unsigned int _screenBuffer, _screenTexture, _stencilMask;

		const char* _stencilPath;

		unsigned int _quadVAO, _quadVBO;

		//TODO: lighting class/rename
		glm::vec3 _lightPosition, _lightDirection, _lightColor; // Note light position isn't used for directional lights and light direction isn't used for point lights

	//Functions
	public:

		//Constructors
		Renderer();

		Renderer(int width, int height);

		//Destructor
		~Renderer();

		//Function for configuring buffers
		void genBuffers();

		//Render the scene
		void renderScene(const Scene& scene, const Camera& camera);

	private:
		void shadowPass(const Scene& scene, RenderData data);

		void geometryPass(const Scene& scene, RenderData data);
		
		void lightingPass(const Scene& scene, RenderData data);

		void postProcessing(const Scene& scene, RenderData data);
	};
}