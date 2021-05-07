#include "AssaultRifle.h"

AssaultRifle::AssaultRifle(const spty::Transform& data, spty::Model* model)
	: Weapon(DAMAGE, MAX_AMMO, RELOAD_TIME, SHOT_COOLDOWN, data, model)
{
	soundPlayer_ = new spty::SoundEffectsPlayer();
	fireSound_ = spty::SoundEffectsLibrary::load("Data/Sounds/Serious/gunFire.wav");
	reloadSound_ = spty::SoundEffectsLibrary::load("Data/Sounds/Serious/gunReload.ogg");
	emptySound_ = spty::SoundEffectsLibrary::load("Data/Sounds/Serious/gunEmpty.wav");
}

AssaultRifle::~AssaultRifle()
{
	delete soundPlayer_;
	spty::SoundEffectsLibrary::unLoad(fireSound_);
	spty::SoundEffectsLibrary::unLoad(emptySound_);
	spty::SoundEffectsLibrary::unLoad(reloadSound_);
}

void AssaultRifle::update(float& deltaTime)
{
	soundPlayer_->setPosition(transform_.getPosition());

	if (cooldownAccum_ < shotCooldown_)
		cooldownAccum_ += deltaTime;

	if (reloadAccum_ < reloadTime_)
	{
		reloadAccum_ += deltaTime;
		return;
	}
	
	if(reloading_)
	{
		transform_.setRoll(0.0f);
		ammoCount_ = maxAmmo_;
		reloading_ = false;
	}

}

void AssaultRifle::fire()
{
	if (reloading_) return;

	if (ammoCount_ == 0)
	{
		if (!hasFired_ && !reloading_)
		{
			soundPlayer_->play(emptySound_);
			hasFired_ = true;
		}
		return;
	}


	if (cooldownAccum_ < shotCooldown_) return;

	transform_.move(transform_.getFront() * 0.1f);
	soundPlayer_->play(fireSound_);

	ammoCount_--;
	cooldownAccum_ = 0.0f;

	spty::RayCallback rayData = spty::Physics::Raycast(transform_.getPosition(), -transform_.getFront() * 1000.0f);

	if (!rayData.hasHit()) return;

	DamageEvent DE = DamageEvent(rayData.m_collisionObject, damage_, -transform_.getFront());
	spty::Dispatcher<GameEventType>::post(DE);
}

void AssaultRifle::reload()
{
	if (reloadAccum_ < reloadTime_ || ammoCount_ == maxAmmo_) return;

	transform_.setRoll(-45.0f);

	reloadAccum_ = 0.0f;
	reloading_ = true;

	soundPlayer_->play(reloadSound_);
}
