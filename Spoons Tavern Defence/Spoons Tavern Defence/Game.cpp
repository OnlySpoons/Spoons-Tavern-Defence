#include "Game.h"

#include "GameObject.h"
#include "Skybox.h"
#include "PhysicsEntity.h"

#include "AssaultRifle.h"

//Constructor
Game::Game() : Engine()
{
	//Load the current Scene
	loadOverworld();

	Weapon* startingWeapon = new AssaultRifle(
		spty::Transform(
			glm::vec3(0.1f, 0.0f, 0.2f), //position
			glm::vec3(0.0f), //rotation
			glm::vec3(0.0005f) //scale
		),
		"Data/Models/gun/SK_Web_RifleSwat_01.fbx"
	);

	_currentScene->addObject(startingWeapon);

	_player = new Player(
		startingWeapon,
		spty::Transform(
			glm::vec3(0.0f, 0.5f, 10.0f), //position
			glm::vec3(0.0f), //rotation
			glm::vec3(0.3f, 0.7f, 0.3f) //scale
		)
	);

	_currentScene->addObject(_player);

	using namespace spty;

	Dispatcher<GameEventType>::subscribe(DamageEvent::Type,
		[&](Event<GameEventType>& e)
		{
			DamageEvent Damage = EventCast<DamageEvent>(e);

			std::cout << Damage.amount << std::endl;

			e.handle();
		}
	);

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

	spty::PhysicsEntity* demo = new spty::PhysicsEntity(
		spty::Transform(
			glm::vec3(0.0f), //position
			glm::vec3(0.0f), //rotation
			glm::vec3(0.005f) //scale
		),
		//"Data/Models/gun/SK_Web_RifleSwat_01.fbx"
		"Data/Models/SyntyStudios/PolygonHeist/Main_Scene_V0.8_Test.fbx"
	);

	demo->enable(); //enable the object to be drawn

	demo->setKinematic(true);

	_currentScene->addObject(demo);

	//TODO: add other objects as required.

	_scenes.emplace_back(_currentScene);
}