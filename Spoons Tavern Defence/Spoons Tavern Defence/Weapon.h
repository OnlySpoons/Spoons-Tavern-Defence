#pragma once
#include "Entity.h"

class Weapon : public spty::Entity
{
public:
	int _damage, _maxAmmo, _ammoCount;
	float _reloadTime, _shotCooldown;

	Weapon(int damage, int maxAmmo, 
		   float reloadTime, float shotCooldown,
		   const spty::Transform&	data,
		   spty::Model* model = nullptr
	)
		: Entity(data, model),
		_damage(damage), _maxAmmo(maxAmmo), _ammoCount(maxAmmo),
		_reloadTime(reloadTime),
		_shotCooldown(shotCooldown)
	{
	}

	virtual ~Weapon() {}

	virtual void update(float& deltaTime) override = 0;

	virtual void fire() = 0;

	virtual void reload() = 0;
};