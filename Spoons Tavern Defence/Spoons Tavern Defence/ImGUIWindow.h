#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <functional>

#include <imgui.h>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Window.h"

namespace spty {
	class ImGUIWindow
	{
	//Variables
	private:
		Window* window_;

	//Functions
	public:
		using ImguiDrawFunc = std::function<void()>;

		//Constructor
		ImGUIWindow(Window* window);

		void attach();
		void detach();

		void imGUIRender(ImguiDrawFunc draw);

		void begin();
		void end();
	};

}