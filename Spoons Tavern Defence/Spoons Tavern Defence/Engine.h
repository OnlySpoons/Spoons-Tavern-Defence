#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <vector>

#include "Window.h"
#include "ImGUIWindow.h"
#include "Renderer.h"
#include "Player.h"
#include "Scene.h"

#include "SoundEffectsLibrary.h"

namespace spty {
	class Engine
	{
	//Variables
	protected:
		Window* window_;
		ImGUIWindow* imguiWindow_;
		ImGUIWindow::ImguiDrawFunc imguiDraw_;
		
		Renderer* renderer_;
		Scene* currentScene_;
		std::vector<spty::Scene*> scenes_;

		Actor* player_;

		float lastFrame_;

	public:
		float deltaTime_;

	//Functions
	public:

		//Constructor
		Engine(Scene* scene = nullptr);

		//Destructor
		virtual ~Engine();

		bool isRunning() const;

		void runtimeLoop();

	private:
		virtual void gameLoop(float& deltaTime) = 0;
	};
}