#pragma once
#include <vector>

#include "Engine.h"
#include "Scene.h"
#include "Shader.h"

class Game : public Spoonity::Engine
{
	//Variables
public:

	//Functions
public:

	//Constructor
	Game();

	//Destructor
	~Game();

	//Overriding gameloop
	void gameLoop(float& deltaTime) override;

	//Load default scene
	Spoonity::Scene* loadOverworld();
};