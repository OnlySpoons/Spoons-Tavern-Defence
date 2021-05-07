#include "Zombie.h"

Zombie::Zombie(const spty::Transform& data, spty::Model* model, const spty::Transform& target, std::mt19937 seed, int wave)
	: PhysicsEntity(data, model, new spty::CapsuleCollider(60.0f, 140.0f)),
	seed_(seed),
	_blendedAI(
		BlendedSteering::BehaviourList(
			{
				{ Seek(transform_, target, MAX_ACCELERATION), WEIGHT },
				{ Align(transform_, target, MAX_ANGULAR_ACCELERATION, ROTATION, TARGET_RADIUS, SLOW_RADIUS), WEIGHT }
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

			if (damage.target == rigidBody_.getBulletBody())
			{
				health_ -= damage.amount;
				_velocity += damage.direction * 2.5f;

				if(isEnabled_)
				{
					ScoreEvent SE(10);
					spty::Dispatcher<GameEventType>::post(SE);
				}

				e.handle();
			}
		}
	);

	soundPlayer_ = new spty::SoundEffectsPlayer();
	_moanSound = spty::SoundEffectsLibrary::load("Data/Sounds/Serious/zombieMoan.wav");
	_hitSound = spty::SoundEffectsLibrary::load("Data/Sounds/Serious/zombieHit.wav");
	deathSound_ = spty::SoundEffectsLibrary::load("Data/Sounds/Serious/zombieDeath.wav");

	health_ += (BONUS_HEALTH * wave);
	damage_ += (BONUS_DAMAGE * wave);
}

Zombie::~Zombie()
{
	delete soundPlayer_;
	spty::SoundEffectsLibrary::unLoad(_moanSound);
	spty::SoundEffectsLibrary::unLoad(_hitSound);
	spty::SoundEffectsLibrary::unLoad(deathSound_);
}

void Zombie::draw(const spty::Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, spty::PassType pass)
{
	transform_.move(WorldDir::DOWN * _drawOffset);
	PhysicsEntity::draw(shader, projection, view, model, pass);
	transform_.move(WorldDir::UP * _drawOffset);
}

void Zombie::update(float& deltaTime)
{
	if (!isEnabled_) return;

	if (health_ <= 0) return die();

	if (_attackCooldownAccum < _attackCooldown)
		_attackCooldownAccum += deltaTime;

	move(deltaTime * _blendedAI.getSteering());
	attack();

	soundPlayer_->setPosition(transform_.getPosition());

	std::uniform_int_distribution moanPercent(0, 100);
	if (moanPercent(seed_) < 2 && !isMoaning)
	{
		isMoaning = true;
		soundPlayer_->play(_moanSound);
	}
	
	if (!soundPlayer_->isPlaying(_moanSound))
		isMoaning = false;
}

void Zombie::move(SteeringOutput movementAI)
{
	rigidBody_.move(_velocity);
	transform_.yaw(transform_.getAngularVelocity());

	transform_.setAngularVelocity(std::fmod(transform_.getAngularVelocity(), 2 * spty::PI));
	transform_.addAngularVelocity(movementAI.Angular);

	movementAI.Linear.y = 0.0f;
	_velocity = movementAI.Linear;
}

void Zombie::attack()
{
	if (_attackCooldownAccum < _attackCooldown) return;

	glm::vec3 dist = _blendedAI.getTargetPosition() - transform_.getPosition();
	float length = glm::length(dist);
	if (length >= 0.5f) return;

	PlayerDamageEvent PDE = PlayerDamageEvent(damage_, glm::normalize(dist));
	spty::Dispatcher<GameEventType>::post(PDE);
	_attackCooldownAccum = 0.0f;
}

void Zombie::die()
{
	ScoreEvent SE = ScoreEvent(100);
	spty::Dispatcher<GameEventType>::post(SE);

	soundPlayer_->play(deathSound_);

	disable();
}
