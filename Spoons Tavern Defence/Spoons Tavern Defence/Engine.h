#pragma once

#include "Window.h"
#include "Camera.h"
#include "Renderer.h"
#include "Input.h"

namespace GameEngine {

	class Engine
	{

	//Memeber variables
	private:
		Window _Window;

		Camera _Camera;

		Renderer _Renderer;
		
		float _LastFrame;

	public:
		float _DeltaTime;

		/* Move to Scene*/
		Skybox sky;

	//Functions
	public:

		//Constructor
		Engine();

		//Destructor
		~Engine();

		//Function for controlling runtime loop
		void runtimeLoop();

		//Function to check if the engine is running
		bool isRunning() const;
	};
}