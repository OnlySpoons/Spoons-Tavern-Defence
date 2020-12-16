#pragma once
#include "Actor.h"
#include "Camera.h"

class Player : public Spoonity::Actor
{

//Variables
public:

//Functions
public:

	//Constructor
	Player(const Spoonity::ObjectData& const data,
		   const std::string&		   const modelPath = "",
		   const Spoonity::Shader&	   const shader = Spoonity::Shader()
	);

	//Render the player Model
	void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model) override;

	//Update the player
	void update(float& deltaTime) override;

	//Processes the keyboard input to control camera movement
	void ProcessKeyboard(Spoonity::Movement direction, float deltaTime, bool isSprinting) override;

	//Processes the mouse movement to control where the camera is facing
	void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true) override;

	//Processes the scroll wheel to control the zoom
	void ProcessMouseScroll(float yOffset) override;
};