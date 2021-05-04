#include "Overworld.h"

Overworld::Overworld()
	: Scene(), _worldModel( new spty::Model("Data/Models/SyntyStudios/PolygonHeist/Main_Scene_V1.0.6.fbx") )
{
	spty::Skybox* sky = new spty::Skybox(
		spty::Transform(),
		std::vector<std::string>(
			{
				"Data/Textures/skybox/right.jpg",
				"Data/Textures/skybox/left.jpg",
				"Data/Textures/skybox/top.jpg",
				"Data/Textures/skybox/bottom.jpg",
				"Data/Textures/skybox/front.jpg",
				"Data/Textures/skybox/back.jpg"
			}
			),
		spty::Shader("Data/Shaders/Skybox/skybox_shader.vs", "Data/Shaders/Skybox/skybox_shader.fs")
	);

	addObject(sky);

	spty::PhysicsEntity* demo = new spty::PhysicsEntity(
		spty::Transform(
			glm::vec3(0.0f), //position
			glm::vec3(0.0f), //rotation
			glm::vec3(0.005f) //scale
		),
		_worldModel
	);

	demo->enable(); //enable the object to be drawn

	demo->setKinematic(true);

	addObject(demo);
}