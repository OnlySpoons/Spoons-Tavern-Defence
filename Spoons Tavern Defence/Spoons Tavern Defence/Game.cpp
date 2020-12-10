#include "Game.h"

Game::Game() : Engine()
{
	_Scenes.emplace_back(loadOverworld());

	//Determine default scene, and pass it to the renderer.
	for (auto it = _Scenes.begin(); it != _Scenes.end(); it++)
	{
		if ((*it)->_ID == Overworld)
		{
			_Renderer._CurrentScene = *it;
		}
	}
}

//Overriding gameloop
void Game::gameLoop(float& deltaTime)
{
	//TODO: Game logic
}

//Load default scene
GameEngine::Scene* Game::loadOverworld()
{
	//Create the objects vector to be passed to the scene
	std::vector<GameEngine::GameObject*> *objs = new std::vector<GameEngine::GameObject*>();

	GameEngine::Skybox* sky = new GameEngine::Skybox(
		ObjectData(),
		std::vector<std::string>(
			{
				"Data/Textures/skybox/right.jpg",
				"Data/Textures/skybox/left.jpg",
				"Data/Textures/skybox/top.jpg",
				"Data/Textures/skybox/bottom.jpg",
				"Data/Textures/skybox/front.jpg",
				"Data/Textures/skybox/back.jpg"
			}),
		Shader("Data/Shaders/skybox_shader.vs", "Data/Shaders/skybox_shader.fs")
	);

	//Add the objects to the scene
	objs->emplace_back(sky);

	GameEngine::Entity* town = new GameEngine::Entity(
		ObjectData(glm::vec3(0.0f), glm::angleAxis(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f))),
		"Data/Models/SyntyStudios/PolygonHeist/Polygon_Heist_Demo_Scene.fbx",
		Shader("Data/Shaders/geometry_shader.vs", "Data/Shaders/geometry_shader.fs")
	);

	objs->emplace_back(town);

	//TODO: add glasses objects as required.


	//Return a scene with the added objects
	return new GameEngine::Scene(Overworld, objs);
}
