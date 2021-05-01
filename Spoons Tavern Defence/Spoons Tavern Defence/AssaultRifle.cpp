#include "AssaultRifle.h"

AssaultRifle::AssaultRifle(const spty::Transform& data, const std::string& modelPath)
	: Weapon(DAMAGE, MAX_AMMO, RELOAD_TIME, SHOT_COOLDOWN, data, modelPath)
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
		std::cout << "empty" << std::endl;
}

void AssaultRifle::fire()
{
	if (_cooldownAccum >= _shotCooldown && _ammoCount > 0)
	{
		glm::vec3 collisionPoint = -_transform.getFront() * 1000.0f;

		spty::RayCallback rayData = spty::Physics::Raycast(_transform.getPosition(), collisionPoint);

		if (rayData.hasHit())
		{
			DamageEvent DE = DamageEvent(rayData.m_collisionObject, _damage);
			spty::Dispatcher<GameEventType>::post(DE);

			//TODO: increase player points
		}

		_ammoCount--;
		_cooldownAccum = 0.0f;
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
