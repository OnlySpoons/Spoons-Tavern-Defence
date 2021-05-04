#pragma once
#include "SoundEffectsPlayer.h"
#include "SoundEffectsLibrary.h"

#include "Weapon.h"

#include "DamageEvent.h"
#include "Dispatcher.h"

class AssaultRifle : public Weapon
{
public:
	static constexpr int DAMAGE = 25, MAX_AMMO = 30;
	static constexpr float RELOAD_TIME = 1.5f, SHOT_COOLDOWN = 0.1f;

	float _reloadAccum = RELOAD_TIME, _cooldownAccum = SHOT_COOLDOWN;
	bool _reloading = false, _firingEmpty = false;
	spty::SoundEffectsPlayer* _soundPlayer;

	int _fireSound, _emptySound, _reloadSound;

	AssaultRifle(const spty::Transform& data, spty::Model* model);

	virtual ~AssaultRifle();

	void update(float& deltaTime) override;

	void fire() override;

	void reload() override;
};

