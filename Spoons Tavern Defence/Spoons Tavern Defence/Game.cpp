#include "Game.h"

Game::Game()
	: Engine(),
	zombieModel_(new spty::Model("Data/Models/SyntyStudios/PolygonWestern/_working/Characters/SK_Character_Badguy_01.fbx")),
	gunModel_(new spty::Model("Data/Models/gun/SK_Web_RifleSwat_01.fbx")),
	seed(rd())
{
	//Handle ScoreEvents
	spty::Dispatcher<GameEventType>::subscribe(ScoreEvent::Type,
		[&](spty::Event<GameEventType>& e)
		{
			ScoreEvent score = spty::EventCast<ScoreEvent>(e);
			score_ += score.amount;
			e.handle();
		}
	);

	//Load the current Scene
	currentScene_ = new Overworld();
	scenes_.emplace_back(currentScene_);

	spawnPlayer();
	
	imguiDraw_ = [&]()
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

		ImGui::Text("Wave: %i", wave_);
		ImGui::Text("Score: %i", score_);

		int numZombies = 0;
		std::for_each(zombies_.begin(), zombies_.end(),
			[&](Zombie* zombie)
			{
				if (zombie->isEnabled_)
				{
					numZombies++;
				}
			}
		);

		ImGui::Text("Zombies Remaining: %i", numZombies);

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

		Player* player = dynamic_cast<Player*>(player_);
		ImGui::Text("Health: %i", player->health_);
		ImGui::Text("Ammo: %2i/%2i", player->gun_->ammoCount_, player->gun_->maxAmmo_);

		ImGui::End();

		if (player->health_ <= 0)
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

	spawnPoints_ = {
		glm::vec3(5.0f, 0.2f, 30.0f),
		glm::vec3(10.0f, 0.2f, 10.0f),
		glm::vec3(1.0f, 0.4f, -2.0f),
		glm::vec3(-10.0f, 0.2f, 20.0f),
		glm::vec3(10.0f, 0.2f, 25.0f)
	};

	music_ = new spty::MusicBuffer("Data/Sounds/Background/marchOfTheSpoons.wav");
	music_->setGain(1.0f);
	music_->play();

	soundPlayer_ = new spty::SoundEffectsPlayer();
	newWaveSound_ = spty::SoundEffectsLibrary::load("Data/Sounds/Memes/ahShit.wav");
	endWaveSound_ = spty::SoundEffectsLibrary::load("Data/Sounds/Memes/yaaaaay.wav");

	//Flag to enable physics debug rendering
	//renderer_->physicsDebug_ = true;
}

Game::~Game()
{
	currentScene_->removeObject(player_);

	delete music_;

	delete soundPlayer_;
	spty::SoundEffectsLibrary::unLoad(newWaveSound_);
	spty::SoundEffectsLibrary::unLoad(endWaveSound_);
}

void Game::gameLoop(float& deltaTime)
{
	if (music_->isPlaying() && music_ != nullptr)
		music_->updateBufferStream();

	if (!waveEnded_)
	{
		
		for (int i = 0; i < zombies_.size(); i++)
			if (zombies_[i]->transform_.getPosition().y < -0.5f)
				zombies_[i]->disable();

		bool killedAll = std::all_of(zombies_.begin(), zombies_.end(), [](Zombie* zombie) { return !(zombie->isEnabled_); });

		if (killedAll && !zombies_.empty())
		{
			for (int i = 0; i < zombies_.size(); i++)
			{
				currentScene_->removeObject(zombies_[i]);
				delete zombies_[i];
			}

			zombies_.clear();

			waveEnded_ = true;
			soundPlayer_->play(endWaveSound_);
		}

		return;
	}

	waveCooldownAccum_ += deltaTime;

	if (waveCooldownAccum_ < waveCooldown_) return;

	waveEnded_ = false;

	if (wave_ != 0)
	{
		soundPlayer_->play(newWaveSound_);
	}

	for (int i = 0; i < zombieCount_ + wave_; i++)
	{
		std::uniform_int_distribution index(0, (int)spawnPoints_.size() - 1);
		std::uniform_real_distribution<float> xOffset(-0.5f, 0.5f), zOffset(-0.5f, 0.5f);

		glm::vec3 spawnPos = spawnPoints_[index(seed)];
		spawnPos += glm::vec3(xOffset(seed), 0.0f, zOffset(seed));
		spawnZombie(spawnPos);
	}

	waveCooldownAccum_ = 0.0f;
	wave_++;
}

void Game::spawnPlayer()
{
	Weapon* startingWeapon = new AssaultRifle(
		spty::Transform(
			glm::vec3(0.1f, 0.0f, 0.2f),	//position
			glm::vec3(0.0f),				//rotation
			glm::vec3(0.0005f)				//scale
		),
		gunModel_
	);

	currentScene_->addObject(startingWeapon);

	player_ = new Player(
		startingWeapon,
		spty::Transform(
			glm::vec3(0.0f, 0.5f, 10.0f),	//position
			glm::vec3(0.0f),				//rotation
			glm::vec3(0.3f, 0.7f, 0.3f)		//scale
		)
	);

	currentScene_->addObject(player_);
}

void Game::spawnZombie(glm::vec3 position)
{
	Zombie* zombie = new Zombie(
		spty::Transform(
			position,			//position
			glm::vec3(0.0f),	//rotation
			glm::vec3(0.005f)	//scale
		),
		zombieModel_,			//Model
		player_->transform_,	//AI target
		seed,					//Mersenne twister generator
		wave_					//Health/Damage multiplier
	);

	zombie->enable();
	zombies_.emplace_back(zombie);
	currentScene_->addObject(zombie);

}
