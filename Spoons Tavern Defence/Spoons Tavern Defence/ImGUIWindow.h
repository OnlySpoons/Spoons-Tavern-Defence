#pragma once

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

		ImGUIWindow(Window* window);

		void attach();
		void detach();

		void imGUIRender();
		void begin();
		void end();
	};

}