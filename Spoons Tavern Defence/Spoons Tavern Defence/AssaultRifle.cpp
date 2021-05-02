#include "AssaultRifle.h"

AssaultRifle::AssaultRifle(const spty::Transform& data, spty::Model* model)
	: Weapon(DAMAGE, MAX_AMMO, RELOAD_TIME, SHOT_COOLDOWN, data, model)
{
}

void AssaultRifle::update(float& deltaTime)
{
	if (_cooldownAccum < _shotCooldown)
	{
		_cooldownAccum += deltaTime;
	}

	if (_reloadAccum < _reloadTime)
	{
		_reloadAccum += deltaTime;
	}

	if (_ammoCount == 0)
		_transform.setRoll(-45.0f);
	else
		_transform.setRoll(0.0f);
}

void AssaultRifle::fire()
{
	if (_ammoCount > 0)
	{
		if (_cooldownAccum >= _shotCooldown)
		{
			spty::RayCallback rayData = spty::Physics::Raycast(_transform.getPosition(), -_transform.getFront() * 1000.0f);

			if (rayData.hasHit())
			{
				DamageEvent DE = DamageEvent(rayData.m_collisionObject, _damage, -_transform.getFront());
				spty::Dispatcher<GameEventType>::post(DE);
			}

			_ammoCount--;
			_cooldownAccum = 0.0f;
		}

		if (_cooldownAccum == 0.0f)
			_transform.move(_transform.getFront() * 0.1f);
		else if (_cooldownAccum >= _shotCooldown)
			_transform.move(-_transform.getFront() * 0.1f);
	}
}

void AssaultRifle::reload()
{
	if (_reloadAccum >= _reloadTime && _ammoCount < _maxAmmo)
	{
		_ammoCount = _maxAmmo;

		_reloadAccum = 0.0f;
	}
}
