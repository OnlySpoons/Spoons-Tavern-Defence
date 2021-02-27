#include "Game.h"

#include "GameObject.h"
#include "Skybox.h"
#include "Entity.h"

//Constructor
Game::Game() : Engine(new Player(Spoonity::ObjectData()))
{
	_scenes.emplace_back(loadOverworld());

	//Determine default scene, and pass it to the renderer.
	for (auto it = _scenes.begin(); it != _scenes.end(); it++)
	{
		if ((*it)->_id == Level::Overworld)
		{
			_currentScene = *it;
		}
	}
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
Spoonity::Scene* Game::loadOverworld()
{
	//Create the objects vector to be passed to the scene
	std::vector<Spoonity::GameObject*>* objs = new std::vector<Spoonity::GameObject*>();

	Spoonity::Skybox* sky = new Spoonity::Skybox(
		Spoonity::ObjectData(),
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

	_renderer->_skybox = sky;

	//Add the objects to the scene
	objs->emplace_back(sky);

	Spoonity::Entity* demo = new Spoonity::Entity(
		Spoonity::ObjectData(
			glm::vec3(0.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f),
			glm::vec3(0.005f)
		),
		"Data/Models/SyntyStudios/PolygonHeist/bank.fbx"
	);

	demo->enable(); //enable the object to be drawn

	objs->emplace_back(demo);

	//TODO: add other objects as required.

	//Return a scene with the added objects
	return new Spoonity::Scene(Level::Overworld, objs);
}