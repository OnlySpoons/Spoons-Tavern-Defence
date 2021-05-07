#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include "Camera.h"
#include "Shader.h"
#include "PassType.h"
#include "Scene.h"

#include "Physics.h"
#include "BulletDebugDrawer.h"
	
namespace spty {
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
		const unsigned int SHADOW_WIDTH = 8192, SHADOW_HEIGHT = 8192;

	public:
		Shader postProcessShader_;

		bool physicsDebug_ = false;

	private:
		Shader depthShader_, geometryShader_, lightingShader_, debugDepthShader_;

		BulletDebugDrawer debugDrawer_;

		unsigned int windowWidth_, windowHeight_;

		unsigned int depthMapFBO_, depthMap_;

		unsigned int gBuffer_, gPosition_, gNormal_, gAlbedoSpec_;

		unsigned int screenBuffer_, screenTexture_, stencilMask_;

		const char* stencilPath_;

		unsigned int quadVAO_, quadVBO_;

		//Note light position isn't used for directional lights and light direction isn't used for point lights
		glm::vec3 lightPosition_, lightDirection_, lightColor_; 

	//Functions
	public:
		//Constructors
		Renderer();
		Renderer(int width, int height);

		//Destructor
		~Renderer();

		void genBuffers();

		void renderScene(const Scene& scene, const Camera& camera);

	private:
		//Render from the light perspective to get shadows
		void shadowPass(const Scene& scene, RenderData& data);

		//Render geometry/colour data to gBuffer
		void geometryPass(const Scene& scene, RenderData& data);

		//Calculate lighting on the gbuffer content
		void lightingPass(const Scene& scene, RenderData& data);

		//Apply post processing to screen texture
		void postProcessing(const Scene& scene, RenderData& data);

		//Blit buffer data
		void blitFramebuffer();
	};
}