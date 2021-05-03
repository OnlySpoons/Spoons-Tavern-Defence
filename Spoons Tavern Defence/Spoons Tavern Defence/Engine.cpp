#include "Engine.h"

namespace spty {

	Engine::Engine(Scene* scene) 
		: _lastFrame(0.0f), _deltaTime(0.0f),
		_currentScene(scene), _player(nullptr)
	{
		_window = new Window(WindowProps("Spoonity", 1920, 1080));

		//Initialise physics
		Physics::init();

		_renderer = new Renderer(_window->getWidth(), _window->getHeight());

		//Initialise input
		Input::setWindow(_window);

		SoundDevice::init();
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

		delete _player;
		Physics::cleanup();

		delete SoundDevice::get();

		delete _renderer;
		delete _window;

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

		//Physics update
		Physics::Update(_deltaTime, *_currentScene);

		_currentScene->update(_deltaTime);

		//Run gameloop
		gameLoop(_deltaTime);

		//Render
		_renderer->renderScene( *_currentScene, *(_player->_camera) );
		glfwSwapBuffers(_window->getInstance());
	}

	//Function to check if the engine is running
	bool Engine::isRunning() const
	{
		return !glfwWindowShouldClose(_window->getInstance());
	}
}