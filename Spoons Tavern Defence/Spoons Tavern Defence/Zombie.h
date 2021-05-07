#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
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

	std::mt19937 seed_;

//Variables
public:
	int health_ = BASE_HEALTH, damage_ = BASE_DAMAGE;
	float _attackCooldown = ATTACK_COOLDOWN;
	float _attackCooldownAccum = 0.0f;

	glm::vec3 _velocity = glm::vec3(0.0f);
	float _maxSpeed = 30.0f;

	BlendedSteering _blendedAI;

	spty::SoundEffectsPlayer* soundPlayer_;
	spty::SoundEffect _moanSound, _hitSound, deathSound_;
	bool isMoaning = false;

	float _drawOffset = 0.65f;

//Functions
public:
	//Constructor
	Zombie(const spty::Transform& data, spty::Model* model, const spty::Transform& target, std::mt19937 seed, int wave);

	//Destructor
	virtual ~Zombie();

	virtual void draw(const spty::Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, spty::PassType pass) override;

	void update(float& deltaTime) override;

	void move(SteeringOutput movementAI);
	void attack();
	void die();
};