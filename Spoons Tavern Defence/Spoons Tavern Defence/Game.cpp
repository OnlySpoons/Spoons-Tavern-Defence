#include "Game.h"

//Constructor
Game::Game() : Engine( new Player(Spoonity::ObjectData( glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(1.0f), 2.5f )) )
{

	//initEngine();

	_Scenes.emplace_back(loadOverworld());

	//Determine default scene, and pass it to the renderer.
	for (auto it = _Scenes.begin(); it != _Scenes.end(); it++)
	{
		if ((*it)->_ID == Overworld)
		{
			_Renderer->_CurrentScene = *it;
		}
	}
}

//Destructor
Game::~Game()
{
	_Scenes.clear();
}

//Overriding gameloop
void Game::gameLoop(float& deltaTime)
{
	//TODO: Game logic
	_Player->update(deltaTime);
}

//Load default scene
Spoonity::Scene* Game::loadOverworld()
{
	//Create the objects vector to be passed to the scene
	std::vector<Spoonity::GameObject*> *objs = new std::vector<Spoonity::GameObject*>();

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
		Spoonity::Shader("Data/Shaders/skybox_shader.vs", "Data/Shaders/skybox_shader.fs")
	);

	//Add the objects to the scene
	objs->emplace_back(sky);

	Spoonity::Entity* town = new Spoonity::Entity(
		Spoonity::ObjectData(
			glm::vec3(0.0f), 
			glm::vec3(0.0f, -1.0f, 0.0f),
			glm::vec3(0.005f)
		),
		"Data/Models/SyntyStudios/PolygonHeist/Polygon_Heist_Demo_Scene.fbx",
		Spoonity::Shader("Data/Shaders/geometry_shader.vs", "Data/Shaders/geometry_shader.fs")
	);

	town->enable(); //enable the object to be drawn

	objs->emplace_back(town);

	//TODO: add other objects as required.


	//Return a scene with the added objects
	return new Spoonity::Scene(Overworld, objs);
}