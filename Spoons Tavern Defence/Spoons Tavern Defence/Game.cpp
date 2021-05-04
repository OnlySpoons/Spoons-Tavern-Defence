#include "Game.h"

//Constructor
Game::Game()
	: Engine(),
	seed(rd()),
	_gunModel(new spty::Model("Data/Models/gun/SK_Web_RifleSwat_01.fbx")),
	_zombieModel(new spty::Model("Data/Models/SyntyStudios/PolygonWestern/_working/Characters/SK_Character_Badguy_01.fbx"))
{
	//Handle ScoreEvents
	spty::Dispatcher<GameEventType>::subscribe(ScoreEvent::Type,
		[&](spty::Event<GameEventType>& e)
		{
			ScoreEvent score = spty::EventCast<ScoreEvent>(e);
			_score += score.amount;
			e.handle();
		}
	);

	//Load the current Scene
	_currentScene = new Overworld();
	_scenes.emplace_back(_currentScene);

	spawnPlayer();

	_spawnPoints = {
		glm::vec3(5.0f, 0.2f, 30.0f),
		glm::vec3(10.0f, 0.2f, 10.0f),
		glm::vec3(1.0f, 0.4f, -2.0f),
		glm::vec3(-10.0f, 0.2f, 20.0f),
		glm::vec3(0.0f, 0.2f, 25.0f)
	};

	_music = new spty::MusicBuffer("Data/Sounds/Background/marchOfTheSpoons.wav");
	_music->SetGain(0.5f);
	_music->Play();

	_soundPlayer = new spty::SoundEffectsPlayer();
	_newWaveSound = spty::SoundEffectsLibrary::load("Data/Sounds/Memes/yaaaaay.wav");
	_endWaveSound = spty::SoundEffectsLibrary::load("Data/Sounds/Memes/ahShit.wav");

	_imguiDraw = [&]()
	{
		ImGuiWindowFlags window_flags
			= ImGuiWindowFlags_NoMove
			| ImGuiWindowFlags_NoResize
			| ImGuiWindowFlags_NoTitleBar
			| ImGuiWindowFlags_NoCollapse
			| ImGuiWindowFlags_AlwaysAutoResize
			| ImGuiWindowFlags_NoSavedSettings;
		bool open = true;

		//Game Stats window
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 0.0f, 0.0f, 0.2f));
		ImGui::Begin("Stats", &open, window_flags);
		
		ImGui::PopStyleColor();
		ImGui::SetWindowFontScale(2.0f);
		ImVec2 winPos = ImGui::GetWindowPos();
		winPos.x -= 20.0f;
		winPos.y -= 20.0f;
		ImGui::SetWindowPos("Stats", winPos, ImGuiCond_Once);

		ImGui::Text("Wave: %i", _wave);
		ImGui::Text("Score: %i\n", _score);

		ImGui::End();

		//Player stats window
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(1.0f, 0.0f, 0.0f, 0.2f));
		ImGui::Begin("Player", &open, window_flags);

		ImGui::PopStyleColor();
		ImGui::SetWindowFontScale(2.0f);
		winPos = ImGui::GetWindowPos();
		winPos.x -= 20.0f;
		winPos.y += 850.0f;
		ImGui::SetWindowPos("Player", winPos, ImGuiCond_Once);

		Player* player = dynamic_cast<Player*>(_player);
		ImGui::Text("Health: %i", player->_health);
		ImGui::Text("Ammo: %2i/%2i", player->_gun->_ammoCount, player->_gun->_maxAmmo);

		ImGui::End();

		if (player->_health <= 0)
		{
			ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
			ImGui::Begin("GameOver", &open, window_flags);

			ImGui::PopStyleColor();
			ImGui::SetWindowFontScale(20.0f);
			winPos = ImGui::GetWindowPos();
			winPos.x += 300.0f;
			winPos.y += 400.0f;
			ImGui::SetWindowPos("GameOver", winPos, ImGuiCond_Once);
			
			ImGui::Text("Game Over!");

			ImGui::End();
		}
	};

	//_renderer->_physicsDebug = true;
}

//Destructor
Game::~Game()
{
	_currentScene->removeObject(_player);

	delete _music;

	delete _soundPlayer;
	spty::SoundEffectsLibrary::unLoad(_newWaveSound);
	spty::SoundEffectsLibrary::unLoad(_endWaveSound);
}

//Overriding gameloop
void Game::gameLoop(float& deltaTime)
{
	if (_music->isPlaying() && _music != nullptr)
		_music->UpdateBufferStream();

	if (_waveEnded)
	{
		_waveCooldownAccum += deltaTime;

		if (_waveCooldownAccum >= _waveCooldown)
		{
			_waveEnded = false;

			for (int i = 0; i < _zombieCount; i++)
			{
				std::uniform_int_distribution index( 0, (int)_spawnPoints.size() - 1 );
				std::uniform_real_distribution<float> xOffset( -0.5f, 0.5f ), zOffset( -0.5f, 0.5f );

				glm::vec3 spawnPos = _spawnPoints[ index( seed ) ];
				spawnPos += glm::vec3( xOffset(seed), 0.0f, zOffset(seed) );
				spawnZombie( spawnPos );
			}

			static bool firstWave = true;
			if (!firstWave)
			{
				_soundPlayer->Play(_newWaveSound);
				firstWave = false;
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
	
	if (killedAll && !_zombies.empty())
	{
		for (int i = 0; i < _zombies.size(); i++)
		{
			_currentScene->removeObject(_zombies[i]);
			delete _zombies[i];
		}

		_zombies.clear();

		_waveEnded = true;
		_soundPlayer->Play(_newWaveSound);
	}

	//TODO: display score & round number
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
		seed,					//Mersenne twister generator
		_wave					//Health/Damage multiplier
	);

	zombie->enable();

	_zombies.emplace_back(zombie);
	_currentScene->addObject(zombie);

}
