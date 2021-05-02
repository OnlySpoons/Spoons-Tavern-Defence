#include "ImGUIWindow.h"

namespace spty {

	ImGUIWindow::ImGUIWindow(Window* window)
		: _window(window) 
	{
		_window->getInstance();
	}

	void ImGUIWindow::attach()
	{
		//Set up ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;	//Enable keyboard controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;	//Enable gamepad controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		//Enable docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;		//Enable multi-viewport
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		//Set up ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		//When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		_window->getInstance();
		GLFWwindow* glfwWindow = static_cast<GLFWwindow*>(_window->getInstance());

		//Set up platform/renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGUIWindow::detach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGUIWindow::imGUIRender()
	{
		//TEMP
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void ImGUIWindow::begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGUIWindow::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		_window->getInstance();
		io.DisplaySize = ImVec2((float)_window->getWidth(), (float)_window->getHeight());

		//Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();

			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();

			glfwMakeContextCurrent(backup_current_context);
		}
	}

}