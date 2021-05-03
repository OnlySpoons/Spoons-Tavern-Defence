#include "AssaultRifle.h"

AssaultRifle::AssaultRifle(const spty::Transform& data, spty::Model* model)
	: Weapon(DAMAGE, MAX_AMMO, RELOAD_TIME, SHOT_COOLDOWN, data, model),
	_soundPlayer(new spty::SoundEffectsPlayer()),
	_fireSound(spty::SoundEffectsLibrary::load("Data/Sounds/bounce.wav")),
	_reloadSound(spty::SoundEffectsLibrary::load("Data/Sounds/bounce.wav")),
	_emptySound(spty::SoundEffectsLibrary::load("Data/Sounds/bounce.wav"))
{
}

AssaultRifle::~AssaultRifle()
{
	delete _soundPlayer;
	spty::SoundEffectsLibrary::unLoad(_fireSound);
	spty::SoundEffectsLibrary::unLoad(_emptySound);
	spty::SoundEffectsLibrary::unLoad(_reloadSound);
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
	else
		_transform.setRoll(0.0f);

	_soundPlayer->SetPosition(_transform.getPosition());
}

void AssaultRifle::fire()
{
	if (_ammoCount > 0 && _reloadAccum >= _reloadTime)
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

		_soundPlayer->Play(_fireSound);
	}
	else
		_soundPlayer->Play(_emptySound);
}

void AssaultRifle::reload()
{
	if (_reloadAccum >= _reloadTime && _ammoCount < _maxAmmo)
	{
		_transform.setRoll(-45.0f);

		_ammoCount = _maxAmmo;

		_reloadAccum = 0.0f;

		_soundPlayer->Play(_reloadSound);
	}
}
