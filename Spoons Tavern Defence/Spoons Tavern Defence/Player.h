#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include "Actor.h"

#include "SoundDevice.h"
#include "SoundEffectsPlayer.h"
#include "SoundEffectsLibrary.h"

#include "Dispatcher.h"
#include "PlayerDamageEvent.h"

#include "AssaultRifle.h"

class Player : public spty::Actor
{
	static constexpr int MAX_HEALTH = 100;
	static constexpr float SPEED = 70.0f, JUMP_HEIGHT = 50.0f;

//Variables
public:
	int health_ = MAX_HEALTH;

	Weapon* gun_;

private:
	glm::vec3 cameraOffset_;

	float speed_ = SPEED, jumpHeight_ = JUMP_HEIGHT;

	spty::SoundEffectsPlayer* soundPlayer_;

	spty::SoundEffect hurtSound_, deathSound_;

//Functions
public:
	//Constructor
	Player(Weapon* gun, const spty::Transform& data, const std::string& modelPath = "");

	virtual ~Player();

	void update(float& deltaTime) override;
	void physicsUpdate() override;

	void processInput(float& deltaTime);

	void setWeapon(Weapon* gun) { gun_ = gun; }

	const btRigidBody* getRigidBody() { return (rigidBody_.getBulletBody()); }
};