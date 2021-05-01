#include "Zombie.h"

Zombie::Zombie(const spty::Transform& data, const std::string& modelPath, const spty::Transform& target)
	: PhysicsEntity(data, modelPath, new spty::CapsuleCollider(60.0f, 140.0f)),
	_health(MAX_HEALTH),
	_damage(BASE_DAMAGE),
	_attackCooldown(ATTACK_COOLDOWN),
	_roundMultiplier(1),
	_blendedAI(
		BlendedSteering::BehaviourList(
			{
				{ Seek(_transform, target, MAX_ACCELERATION), WEIGHT },
				{ Align(_transform, target, MAX_ANGULAR_ACCELERATION, ROTATION, TARGET_RADIUS, SLOW_RADIUS), WEIGHT }
			}
		),
		MAX_ACCELERATION, MAX_ANGULAR_ACCELERATION
	)
{

	using namespace spty;

	Dispatcher<GameEventType>::subscribe(DamageEvent::Type,
		[&](Event<GameEventType>& e)
		{
			DamageEvent Damage = EventCast<DamageEvent>(e);

			if (Damage.target == _rigidBody.getBulletBody())
			{
				_health -= Damage.amount;
				e.handle();
			}
		}
	);
}

void Zombie::update(float& deltaTime)
{
	if (_health > 0)
	{
		auto movementAI = _blendedAI.getSteering();

		_rigidBody.move(movementAI._linear * deltaTime);
		_transform.yaw(_transform.getAngularVelocity());

		_transform.setAngularVelocity(std::fmod(_transform.getAngularVelocity(), 2 * spty::PI));
		_transform.addAngularVelocity(movementAI._angular * deltaTime);
	}
	else
		die();

}

void Zombie::attack()
{
	//TODO: check collision with target, when we do AI
}

void Zombie::die()
{
	//TODO
	std::cout << "i've died" << std::endl;
}
