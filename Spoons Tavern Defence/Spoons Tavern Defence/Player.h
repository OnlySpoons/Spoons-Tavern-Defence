#pragma once
#include "Actor.h"
#include "Entity.h"
#include "Camera.h"
#include "SoundDevice.h"
#include "SoundEffectsPlayer.h"
#include "SoundEffectsLibrary.h"

#include "Dispatcher.h"
#include "PlayerDamageEvent.h"

#include "AssaultRifle.h"

class Player : public spty::Actor
{
	static constexpr int MAX_HEALTH = 100;

//Variables
public:
	int _health = MAX_HEALTH;

	Weapon* _gun;

private:
	glm::vec3 _cameraOffset;

	float _speed, _jumpHeight;
	bool _jumping;

	spty::SoundEffectsPlayer* _soundPlayer;

	int _hurtSound, _deathSound;

//Functions
public:

	//Constructor
	Player(Weapon* gun, const spty::Transform& data, const std::string& modelPath = "");

	virtual ~Player();

	//Update the player
	void update(float& deltaTime) override;

	void physicsUpdate() override;

	//Process the input for player controls
	void processInput(float& deltaTime);

	void setWeapon(Weapon* gun) { _gun = gun; }

	const btRigidBody* getRigidBody() { return (_rigidBody.getBulletBody()); }
};