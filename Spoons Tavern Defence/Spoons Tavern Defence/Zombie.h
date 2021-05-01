#pragma once
#include "PhysicsEntity.h"
#include "Dispatcher.h"
#include "DamageEvent.h"

#include "BlendedSteering.h"

class Zombie : public spty::PhysicsEntity
{
	static constexpr int MAX_HEALTH = 100, BASE_DAMAGE = 20;
	static constexpr int ATTACK_COOLDOWN = 2.0f;

	static constexpr float MAX_ACCELERATION = 80.0f, MAX_ANGULAR_ACCELERATION = 20.0f;
	static constexpr float ROTATION = 50.0f;
	static constexpr float TARGET_RADIUS = 5.0f, SLOW_RADIUS = 60.0f;
	static constexpr float WEIGHT = 0.5f;

public:
	int _health, _damage;
	float _attackCooldown;
	int _roundMultiplier;

	glm::vec3 _velocity = glm::vec3(0.0f);
	float _maxSpeed = 30.0f;

	BlendedSteering _blendedAI;

	Zombie(const spty::Transform& data, const std::string& modelPath, const spty::Transform& target);

	virtual ~Zombie() {}

	void update(float& deltaTime) override;

	void attack();

	void die();

	void setRoundMult(int mult) { _roundMultiplier = mult; }

};