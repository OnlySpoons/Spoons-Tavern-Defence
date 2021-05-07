#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Input.h"

namespace spty {
	struct WindowProps
	{
		std::string title;
		unsigned int width;
		unsigned int height;
	};

	//A wrapper class for the GLFWwindow
	class Window
	{
	//Variables
	private:
		GLFWwindow* instance_;

		WindowProps properties_;

	//Functions
	public:
		//Constructor
		Window(WindowProps properties = WindowProps{ "Spoonity", 1280, 720 });

		//Destructor
		~Window();

		GLFWwindow* getInstance() const;

		unsigned int getWidth() const;
		unsigned int getHeight() const;

		void close() const;
	};
}