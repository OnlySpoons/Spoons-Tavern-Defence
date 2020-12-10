#pragma once

#include "Window.h"
#include "Camera.h"
#include "Renderer.h"
#include "Input.h"

namespace GameEngine {

	class Engine
	{

	//Memeber variables
	protected:
		Window _Window;

		Camera _Camera;

		Renderer _Renderer;
		
		float _LastFrame;

	public:
		float _DeltaTime;

	//Functions
	public:

		//Constructor
		Engine();

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