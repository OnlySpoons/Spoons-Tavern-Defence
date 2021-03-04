#pragma once
#include <vector>

#include "Engine.h"
#include "Scene.h"
#include "Shader.h"

enum Level {
	None = -1,
	Overworld = 0,
};

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
	void loadOverworld();
};