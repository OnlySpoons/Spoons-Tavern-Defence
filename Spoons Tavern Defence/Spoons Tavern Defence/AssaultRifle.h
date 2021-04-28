#pragma once
#include "Weapon.h"

#include "DamageEvent.h"
#include "Dispatcher.h"

class AssaultRifle : public Weapon
{
public:
	static constexpr int DAMAGE = 25, MAX_AMMO = 30;
	static constexpr float RELOAD_TIME = 1.5f, SHOT_COOLDOWN = 0.1f;

	float _reloadAccum = RELOAD_TIME, _cooldownAccum = SHOT_COOLDOWN;

	AssaultRifle(const spty::Transform& data, const std::string& modelPath);

	virtual ~AssaultRifle() {}

	void update(float& deltaTime) override;

	void fire() override;

	void reload() override;
};

