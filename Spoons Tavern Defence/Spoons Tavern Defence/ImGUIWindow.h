#pragma once
#include <functional>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Window.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace spty {

	class ImGUIWindow
	{
	private:
		Window* _window;

	public:

		using ImguiDrawFunc = std::function<void()>;

		ImGUIWindow(Window* window);

		void attach();
		void detach();

		void imGUIRender(ImguiDrawFunc draw);

		void begin();
		void end();
	};

}