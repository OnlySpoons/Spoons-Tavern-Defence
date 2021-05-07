#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include "Weapon.h"

#include "SoundEffectsPlayer.h"
#include "SoundEffectsLibrary.h"

#include "Dispatcher.h"
#include "DamageEvent.h"

class AssaultRifle : public Weapon
{
	static constexpr int DAMAGE = 25, MAX_AMMO = 30;
	static constexpr float RELOAD_TIME = 1.5f, SHOT_COOLDOWN = 0.1f;

//Variables
public:
	float reloadAccum_ = RELOAD_TIME, cooldownAccum_ = SHOT_COOLDOWN;
	bool reloading_ = false, hasFired_ = false;
	
	spty::SoundEffectsPlayer* soundPlayer_;

	spty::SoundEffect fireSound_, emptySound_, reloadSound_;

//Functions
public:
	//Constructor
	AssaultRifle(const spty::Transform& data, spty::Model* model);

	//Destructor
	virtual ~AssaultRifle();

	void update(float& deltaTime) override;

	void fire() override;

	void reload() override;
};

