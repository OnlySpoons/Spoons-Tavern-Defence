#include "Zombie.h"

Zombie::Zombie(const spty::Transform& data, spty::Model* model, const spty::Transform& target, int wave)
	: PhysicsEntity(data, model, new spty::CapsuleCollider(60.0f, 140.0f)),
	_drawOffset(0.7f),
	_health(BASE_HEALTH + (BONUS_HEALTH * wave)),
	_damage(BASE_DAMAGE + (BONUS_DAMAGE * wave)),
	_attackCooldown(ATTACK_COOLDOWN),
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
	//Handle DamageEvents
	spty::Dispatcher<GameEventType>::subscribe(DamageEvent::Type,
		[&](spty::Event<GameEventType>& e)
		{
			DamageEvent damage = spty::EventCast<DamageEvent>(e);

			if (damage.target == _rigidBody.getBulletBody())
			{
				_health -= damage.amount;
				_velocity += damage.direction * 2.5f;

				if(_isEnabled)
				{
					ScoreEvent SE(10);
					spty::Dispatcher<GameEventType>::post(SE);
				}

				e.handle();
			}
		}
	);
}

void Zombie::draw(const spty::Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, spty::PassType pass)
{
	_transform.move(WorldDir::DOWN * _drawOffset);
	PhysicsEntity::draw(shader, projection, view, model, pass);
	_transform.move(WorldDir::UP * _drawOffset);
}

void Zombie::update(float& deltaTime)
{
	if (_attackCooldownAccum < _attackCooldown)
		_attackCooldownAccum += deltaTime;

	if (_health > 0)
	{
		move(deltaTime * _blendedAI.getSteering());
		attack();
	}
	else if (_isEnabled)
		die();
}

void Zombie::move(SteeringOutput movementAI)
{
	_rigidBody.move(_velocity);
	_transform.yaw(_transform.getAngularVelocity());

	_transform.setAngularVelocity(std::fmod(_transform.getAngularVelocity(), 2 * spty::PI));
	_transform.addAngularVelocity(movementAI._angular);

	movementAI._linear.y = 0.0f;
	_velocity = movementAI._linear;
}

void Zombie::attack()
{
	if (_attackCooldownAccum >= _attackCooldown)
	{
		glm::vec3 dist = _blendedAI.getTargetPosition() - _transform.getPosition();

		float length = glm::length(dist);
 		if (length < 0.5f)
		{
			PlayerDamageEvent PDE = PlayerDamageEvent(_damage, -glm::normalize(dist));
			spty::Dispatcher<GameEventType>::post(PDE);
		}

		_attackCooldownAccum = 0.0f;
	}
}

void Zombie::die()
{
	//TODO: send score event
	ScoreEvent SE = ScoreEvent(100);
	spty::Dispatcher<GameEventType>::post(SE);

	disable();
}
