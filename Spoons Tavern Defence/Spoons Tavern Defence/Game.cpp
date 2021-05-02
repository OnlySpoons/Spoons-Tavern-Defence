#include "Game.h"

//Constructor
Game::Game()
	: Engine(),
	seed(rd()),
	_gunModel(new spty::Model("Data/Models/gun/SK_Web_RifleSwat_01.fbx")),
	_zombieModel(new spty::Model("Data/Models/SyntyStudios/PolygonWestern/_working/Characters/SK_Character_Badguy_01.fbx"))
{
	//Load the current Scene
	_currentScene = new Overworld();
	_scenes.emplace_back(_currentScene);

	spawnPlayer();

	_spawnPoints = {
		glm::vec3(5.0, 0.5f, 10.0f),
		glm::vec3(0.0, 0.5f, 15.0f)
	};

	//Handle ScoreEvents
	spty::Dispatcher<GameEventType>::subscribe(ScoreEvent::Type,
		[&](spty::Event<GameEventType>& e)
		{
			ScoreEvent score = spty::EventCast<ScoreEvent>(e);
			_score += score.amount;
			e.handle();
		}
	);
}

//Destructor
Game::~Game()
{
	_currentScene->removeObject(_player);
}

//Overriding gameloop
void Game::gameLoop(float& deltaTime)
{
	if (_waveEnded)
	{
		_waveCooldownAccum += deltaTime;

		if (_waveCooldownAccum >= _waveCooldown)
		{
			_waveEnded = false;

			for (int i = 0; i < _zombieCount; i++)
			{
				std::uniform_int_distribution index( 0, (int)_spawnPoints.size() - 1 );
				std::uniform_real_distribution<float> xOffset( -5.0f, 5.0f ), zOffset( -5.0f, 5.0f );

				glm::vec3 spawnPos = _spawnPoints[ index( seed ) ];
				//spawnPos += glm::vec3( xOffset(seed), 0.0f, zOffset(seed) );
				spawnZombie( spawnPos );
			}

			_waveCooldownAccum = 0.0f;
			_wave++;
		}
	}

	bool killedAll = true;
	for (int i = 0; i < _zombies.size(); i++)
	{
		if (_zombies[i]->_transform.getPosition().y < -0.5f)
			_zombies[i]->disable();

		killedAll &= !(_zombies[i]->_isEnabled);
	}
	
	if (killedAll)
	{
		for (int i = 0; i < _zombies.size(); i++)
		{
			_currentScene->removeObject(_zombies[i]);
		}

		_zombies.clear();

		_waveEnded = true;
	}

	//std::cout << _score << std::endl;
}

void Game::spawnPlayer()
{
	Weapon* startingWeapon = new AssaultRifle(
		spty::Transform(
			glm::vec3(0.1f, 0.0f, 0.2f),	//position
			glm::vec3(0.0f),				//rotation
			glm::vec3(0.0005f)				//scale
		),
		_gunModel
	);

	_currentScene->addObject(startingWeapon);

	_player = new Player(
		startingWeapon,
		spty::Transform(
			glm::vec3(0.0f, 0.5f, 10.0f),	//position
			glm::vec3(0.0f),				//rotation
			glm::vec3(0.3f, 0.7f, 0.3f)		//scale
		)
	);

	_currentScene->addObject(_player);
}

void Game::spawnZombie(glm::vec3 position)
{
	Zombie* zombie = new Zombie(
		spty::Transform(
			position,			//position
			glm::vec3(0.0f),	//rotation
			glm::vec3(0.005f)	//scale
		),
		_zombieModel,			//Model
		_player->_transform,	//AI target
		_wave					//Health/Damage multiplier
	);

	zombie->enable();

	_zombies.emplace_back(zombie);
	_currentScene->addObject(zombie);

}
