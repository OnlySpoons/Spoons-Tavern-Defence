#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <random>

#include "Engine.h"

#include "SoundDevice.h"
#include "MusicBuffer.h"
#include "SoundEffectsLibrary.h"
#include "SoundEffectsPlayer.h"

#include "Dispatcher.h"
#include "ScoreEvent.h"

#include "Overworld.h"

#include "AssaultRifle.h"
#include "Zombie.h"


class Game : public spty::Engine
{
//Variables
private:
	std::random_device rd;
	std::mt19937 seed;

public:
	int wave_ = 0, zombieCount_ = 15;
	float waveCooldown_ = 10.0f, waveCooldownAccum_ = 0.0f;
	bool waveEnded_ = true;

	int score_ = 0;
	
	std::vector<glm::vec3> spawnPoints_{};
	std::vector<Zombie*> zombies_{};

	spty::Model *gunModel_, *zombieModel_;

	spty::MusicBuffer* music_;
	spty::SoundEffectsPlayer* soundPlayer_;
	spty::SoundEffect newWaveSound_, endWaveSound_;

//Functions
public:
	//Constructor
	Game();

	//Destructor
	~Game();

	void gameLoop(float& deltaTime) override;

	void spawnPlayer();
	void spawnZombie(glm::vec3 position);
};