#include "Game.h"

#include "GameObject.h"
#include "Skybox.h"
#include "Entity.h"

//Constructor
Game::Game() : Engine()
{
	_player = new Player(
		spty::Transform(
			glm::vec3(0.0f, 0.5f, 0.0f), //position
			glm::vec3(0.0f), //rotation
			glm::vec3(0.5f, 0.7f, 0.5f) //scale
		)
	);

	//Load the current Scene
	loadOverworld();

	_currentScene->addObject(_player);

	//TODO: this shit
	//_scenes.emplace_back(new Overworld());
}

//Destructor
Game::~Game()
{
	_currentScene->removeObject(_player);
}

//Overriding gameloop
void Game::gameLoop(float& deltaTime)
{
	for (auto it = _scenes.begin(); it != _scenes.end(); it++)
	{
		if ((*it)->_id == Level::Overworld)
		{
			(*it)->update(deltaTime);
		}
	}
}

//Load default scene
void Game::loadOverworld()
{
	//Create the scene
	_currentScene = new spty::Scene(Level::Overworld);

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

	_currentScene->addObject(sky);

	spty::Entity* demo = new spty::Entity(
		spty::Transform(
			glm::vec3(0.0f), //position
			glm::vec3(0.0f), //rotation
			glm::vec3(0.005f) //scale
		),
		//"Data/Models/gun/SK_Web_RifleSwat_01.fbx"
		"Data/Models/SyntyStudios/PolygonHeist/bank.fbx"
	);

	demo->enable(); //enable the object to be drawn

	demo->setKinematic(true);

	_currentScene->addObject(demo);

	//demo = new spty::Entity(
	//	spty::Transform(
	//		glm::vec3(0.0f, -1.5f, 0.0f), //position
	//		glm::vec3(0.0f), //rotation
	//		glm::vec3(20.0f, 1.0f, 20.0f) //scale
	//	)
	//);

	//demo->setKinematic(true);

	//_currentScene->addObject(demo);

	//TODO: add other objects as required.

	_scenes.emplace_back(_currentScene);
}