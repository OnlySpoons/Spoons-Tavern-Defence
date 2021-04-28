#pragma once
#include "Actor.h"
#include "Entity.h"
#include "Camera.h"

#include "AssaultRifle.h"

class Player : public spty::Actor
{
//Variables
private:
	glm::vec3 _cameraOffset;

	float _speed, _jumpHeight;
	bool _jumping;

	Weapon* _gun;

//Functions
public:

	//Constructor
	Player(Weapon* gun, const spty::Transform& data,
		const std::string& modelPath = "");

	virtual ~Player();

	//Update the player
	void update(float& deltaTime) override;

	void physicsUpdate() override;

	//Process the input for player controls
	void processInput(float& deltaTime);

	void setWeapon(Weapon* gun) { _gun = gun; }
};