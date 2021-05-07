#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include "Entity.h"

class Weapon : public spty::Entity
{
//Variables
public:
	int damage_, maxAmmo_, ammoCount_;
	float reloadTime_, shotCooldown_;

//Functions
public:
	//Constructor
	Weapon(int damage, int maxAmmo, float reloadTime, float shotCooldown,
		   const spty::Transform& data, spty::Model* model = nullptr)
		: Entity(data, model),
		damage_(damage), maxAmmo_(maxAmmo), ammoCount_(maxAmmo),
		reloadTime_(reloadTime), shotCooldown_(shotCooldown)
	{
	}

	//Destructor
	virtual ~Weapon() {}

	virtual void update(float& deltaTime) override = 0;

	virtual void fire() = 0;

	virtual void reload() = 0;
};