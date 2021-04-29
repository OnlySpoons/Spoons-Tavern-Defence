#pragma once
#include <vector>

#include "Engine.h"
#include "Scene.h"
#include "Shader.h"

//Thomas: TEMP
#include "SoundDevice.h"
#include "SoundBuffer.h"
#include "SoundSource.h"
#include "MusicBuffer.h"

enum Level {
	None = -1,
	Overworld = 0,
};

class Game : public spty::Engine
{
	//Variables
public:
	spty::SoundDevice* _soundDevice;
	spty::MusicBuffer* _music;
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