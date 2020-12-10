#include "Engine.h"

namespace GameEngine {

	Engine::Engine()
		: _LastFrame(0.0f), _DeltaTime(0.0f),
		_Window(Window(WindowProps("Spoons: Tavern Defence", 1920, 1080))),
		_Camera(Camera(glm::vec3(0.0f, 0.7f, 3.0f))),
		_Renderer(Renderer(&_Window, &_Camera))
	{
		//Initialise input
		Input::init(&_Camera);

	}

	Engine::~Engine()
	{
		glfwTerminate();
	}

	//Function for controlling runtime loop
	void Engine::runtimeLoop()
	{
		//Per-frame time logic
		float currentFrame = (float)glfwGetTime();
		_DeltaTime = currentFrame - _LastFrame;
		_LastFrame = currentFrame;

		//Input
		Input::processInput(_Window.getInstance(), _DeltaTime);

		//Run gameloop
		gameLoop(_DeltaTime);

		//Render
		_Renderer.renderScene();
	}

	//Function to check if the engine is running
	bool Engine::isRunning() const
	{
		return !glfwWindowShouldClose(_Window.getInstance());
	}
}