#pragma once
#include "Actor.h"
#include "Entity.h"
#include "Camera.h"

class Player : public spty::Actor
{
	//Variables
private:
	float _speed;

	glm::vec3 _cameraOffset;

	//Functions
public:

	//Constructor
	Player(const spty::Transform& data,
		const std::string& modelPath = ""
	);

	//Render the player Model
	void draw(const spty::Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, spty::PassType pass) override;

	//Update the player
	void update(float& deltaTime) override;

	void physicsUpdate() override;

	//Process the input for player controls
	void processInput(float& deltaTime);
};