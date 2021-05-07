#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <vector>
#include <string>

#include "stb_image.h"

#include "GameObject.h"
#include "Shader.h"

namespace spty {

	class Skybox : public GameObject
	{
	//Variables
	private:

		Shader shader_;

		//Skybox render data
		std::vector<std::string> textureFaces_;
		unsigned int VAO_, VBO_, cubeTexture_;


	//Functions
	public:
		//Constructor
		Skybox(const Transform& data, const std::vector<std::string>& faces, const Shader& shader);

		//Destructor
		~Skybox();

		void draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass) override;

		//Unused by skybox
		void update(float& deltaTime) override {}
		void physicsUpdate() override {}

	private:
		void InitCubeTexture();

		void genBuffers();
	};
}