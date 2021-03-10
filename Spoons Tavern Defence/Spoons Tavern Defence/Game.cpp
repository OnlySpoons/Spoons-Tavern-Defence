#include "Game.h"

#include "GameObject.h"
#include "Skybox.h"
#include "Entity.h"

//Constructor
Game::Game() : Engine(new Player(Spoonity::Transform()))
{
	//Load the current Scene
	loadOverworld();

	//TODO: this shit
	//_scenes.emplace_back(new Overworld());
}

//Destructor
Game::~Game()
{
}

//Overriding gameloop
void Game::gameLoop(float& deltaTime)
{
	//Update the player
	_player->update(deltaTime);

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
	_currentScene = new Spoonity::Scene(Level::Overworld);

	Spoonity::Skybox* sky = new Spoonity::Skybox(
		Spoonity::Transform(),
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
		Spoonity::Shader("Data/Shaders/Skybox/skybox_shader.vs", "Data/Shaders/Skybox/skybox_shader.fs")
	);

	_currentScene->addObject(sky);

	Spoonity::Entity* demo = new Spoonity::Entity(
		Spoonity::Transform(
			glm::vec3(0.0f), //position
			glm::vec3(0.0f), //rotation
			glm::vec3(0.005f) //scale
		),
		"Data/Models/SyntyStudios/PolygonHeist/bank.fbx"
	);

	demo->enable(); //enable the object to be drawn

	_currentScene->addObject(demo);

	//TODO: add other objects as required.

	_scenes.emplace_back(_currentScene);
}