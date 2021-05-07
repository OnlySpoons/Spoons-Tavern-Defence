#include "Engine.h"

namespace spty {

	Engine::Engine(Scene* scene) 
		: lastFrame_(0.0f), deltaTime_(0.0f),
		currentScene_(scene),
		player_(nullptr)
	{
		window_ = new Window(WindowProps{ "Spoonity", 1920, 1080 });

		Physics::init();

		renderer_ = new Renderer(window_->getWidth(), window_->getHeight());

		Input::setWindow(window_);

		imguiWindow_ = new ImGUIWindow(window_);

		imguiWindow_->attach();

		imguiDraw_ = []{};

		SoundDevice::init();
	}

	Engine::~Engine()
	{
		Input::clearWindow();

		for (auto it = scenes_.begin(); it != scenes_.end(); ++it)
		{
			delete* it;
		}

		scenes_.clear();

		currentScene_ = nullptr;

		delete player_;
		Physics::cleanup();

		delete SoundDevice::get();

		delete renderer_;
		imguiWindow_->detach();
		delete window_;

	}

	//Function for controlling runtime loop
	void Engine::runtimeLoop()
	{
		//Per-frame time logic
		float currentFrame = (float)glfwGetTime();
		deltaTime_ = currentFrame - lastFrame_;
		lastFrame_ = currentFrame;

		//Input
		glfwPollEvents();

		//Physics update
		Physics::Update(deltaTime_, *currentScene_);

		//Update scene
		currentScene_->update(deltaTime_);

		//Run gameloop
		gameLoop(deltaTime_);

		//Render
		renderer_->renderScene( *currentScene_, *(player_->camera_) );

		//IMGUI render
		imguiWindow_->imGUIRender(imguiDraw_);

		glfwSwapBuffers(window_->getInstance());
	}

	//Function to check if the engine is running
	bool Engine::isRunning() const
	{
		return !glfwWindowShouldClose(window_->getInstance());
	}
}