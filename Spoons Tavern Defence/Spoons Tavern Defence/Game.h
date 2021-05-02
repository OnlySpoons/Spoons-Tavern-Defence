#pragma once
#include <random>

#include "Engine.h"
#include "Shader.h"

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
	int _wave = 1, _zombieCount = 2;
	float _waveCooldown = 10.0f, _waveCooldownAccum = 0.0f;
	bool _waveEnded = true;

	int _score = 0;
	
	std::vector<glm::vec3> _spawnPoints{};
	std::vector<Zombie*> _zombies{};

	spty::Model* _gunModel, * _zombieModel;

//Functions
public:

	//Constructor
	Game();

	//Destructor
	~Game();

	//Overriding gameloop
	void gameLoop(float& deltaTime) override;

	void spawnPlayer();

	void spawnZombie(glm::vec3 position);
};