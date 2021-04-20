#pragma once

#include <vector>

#include "Window.h"
#include "Renderer.h"
#include "Player.h"
#include "Scene.h"

namespace spty {

	class Engine
	{

		//Memeber variables
	protected:
		Window* _window;

		Renderer* _renderer;

		Actor* _player;

		std::vector<spty::Scene*> _scenes;

		Scene* _currentScene;

		float _lastFrame;

	public:
		float _deltaTime;

		//Functions
	public:

		//Constructor
		Engine(Scene* scene = nullptr);

		//Destructor
		virtual ~Engine();

		//Function to check if the engine is running
		bool isRunning() const;

		//Function for controlling runtime loop
		void runtimeLoop();

	private:
		virtual void gameLoop(float& deltaTime) = 0;
	};
}