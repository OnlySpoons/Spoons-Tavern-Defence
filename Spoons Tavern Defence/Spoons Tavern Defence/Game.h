#pragma once
#include <vector>

#include "Engine.h"
#include "Scene.h"

#include "GameObject.h"
#include "Skybox.h"
#include "Entity.h"
#include "Glasses.h"

class Game : public GameEngine::Engine
{
//Variables
public:

	std::vector<GameEngine::Scene*> _Scenes;

//Functions
public:

	//Constructor
	Game();

	//Overriding gameloop
	void gameLoop(float& deltaTime) override;

	//Load default scene
	GameEngine::Scene* loadOverworld();

};

