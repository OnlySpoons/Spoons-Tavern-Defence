#pragma once
#include <random>

#include "PhysicsEntity.h"
#include "SoundEffectsPlayer.h"
#include "SoundEffectsLibrary.h"

#include "Dispatcher.h"
#include "DamageEvent.h"
#include "ScoreEvent.h"
#include "PlayerDamageEvent.h"

#include "BlendedSteering.h"

class Zombie : public spty::PhysicsEntity
{
	static constexpr int BASE_HEALTH = 75, BASE_DAMAGE = 20;
	static constexpr int BONUS_HEALTH = 5, BONUS_DAMAGE = 1;
	static constexpr float ATTACK_COOLDOWN = 2.0f;

	static constexpr float MAX_ACCELERATION = 80.0f, MAX_ANGULAR_ACCELERATION = 20.0f;
	static constexpr float ROTATION = 50.0f;
	static constexpr float TARGET_RADIUS = 5.0f, SLOW_RADIUS = 60.0f;
	static constexpr float WEIGHT = 0.5f;

	std::mt19937 _seed;

public:
	int _health, _damage;
	float _attackCooldown;
	float _attackCooldownAccum = 0.0f;

	glm::vec3 _velocity = glm::vec3(0.0f);
	float _maxSpeed = 30.0f;

	BlendedSteering _blendedAI;

	spty::SoundEffectsPlayer* _soundPlayer;
	int _moanSound, _hurtSound, _deathSound;
	bool isMoaning = false;

	float _drawOffset;

	Zombie(const spty::Transform& data, spty::Model* model, const spty::Transform& target, std::mt19937 seed, int wave);

	virtual ~Zombie();

	virtual void draw(const spty::Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, spty::PassType pass) override;

	void update(float& deltaTime) override;

	void move(SteeringOutput movementAI);

	void attack();

	void die();
};