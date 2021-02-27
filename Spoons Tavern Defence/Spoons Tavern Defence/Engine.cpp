#include "Engine.h"

namespace Spoonity {

	Engine::Engine(Actor* player, Scene* scene) 
		: _lastFrame(0.0f), _deltaTime(0.0f),
		_player(player),
		_currentScene(scene)
	{
		_window = new Window(WindowProps("Advanced Graphics Project", 1920, 1080));

		_renderer = new Renderer(_window->getWidth(), _window->getHeight());

		//Initialize input
		Input::setWindow(_window);
	}

	Engine::~Engine()
	{
		Input::clearWindow();

		for (auto it = _scenes.begin(); it != _scenes.end(); ++it)
		{
			delete* it;
		}

		_scenes.clear();

		_currentScene = nullptr;

		delete _renderer;
		delete _window;
		delete _player;
	}

	//Function for controlling runtime loop
	void Engine::runtimeLoop()
	{
		//Per-frame time logic
		float currentFrame = (float)glfwGetTime();
		_deltaTime = currentFrame - _lastFrame;
		_lastFrame = currentFrame;

		//Input
		glfwPollEvents();

		//Run gameloop
		gameLoop(_deltaTime);

		//Render
		_renderer->renderScene(*_currentScene, *_player->_camera);
		glfwSwapBuffers(_window->getInstance());
	}

	//Function to check if the engine is running
	bool Engine::isRunning() const
	{
		return !glfwWindowShouldClose(_window->getInstance());
	}
}