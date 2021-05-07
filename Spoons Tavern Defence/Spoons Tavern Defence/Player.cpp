#include "Player.h"

//Constructor
Player::Player(Weapon* gun,
	const spty::Transform& transform,
	const std::string& modelPath
)
	: Actor(transform, new spty::Camera(), modelPath),
	gun_(gun)
{
	//Handle DamageEvents
	spty::Dispatcher<GameEventType>::subscribe(PlayerDamageEvent::Type,
		[&](spty::Event<GameEventType>& e)
		{
			PlayerDamageEvent damage = spty::EventCast<PlayerDamageEvent>(e);

			if (health_ > 0)
			{
				soundPlayer_->play(hurtSound_);
				health_ -= damage.amount;
				rigidBody_.move(damage.direction * 5.0f);
			}
			e.handle();
		}
	);

	cameraOffset_ = glm::vec3(0.0f, 0.3f, 0.0f);

	transform_.setYaw(180.0f);

	camera_->update(transform_, cameraOffset_);

	rigidBody_.setMass(150.0f);

	gun_->enable();

	spty::SoundDevice::get()->setAttunationModel(spty::AttenuationModel::ClampedLinear);
	spty::SoundDevice::get()->setGain(0.1f);

	soundPlayer_ = new spty::SoundEffectsPlayer();
	hurtSound_ = spty::SoundEffectsLibrary::load("Data/Sounds/Serious/playerHurt.ogg");
	deathSound_ = spty::SoundEffectsLibrary::load("Data/Sounds/Serious/playerDeath.ogg");
}

Player::~Player()
{
	delete soundPlayer_;
	spty::SoundEffectsLibrary::unLoad(hurtSound_);
	spty::SoundEffectsLibrary::unLoad(deathSound_);
}

//Update the player
void Player::update(float& deltaTime)
{
	//Escape closes the window
	if (spty::Input::isKeyPressed(spty::KeyCode::Escape))
		spty::Input::closeWindow();

	if (health_ <= 0)
	{
		static bool died = true;
		if (died)
		{
			died = false;
			soundPlayer_->play(deathSound_);
		}
		return;
	}

	processInput(deltaTime);

	if (onGround())
		rigidBody_.disableGravity();
	else
		rigidBody_.enableGravity();
}

void Player::physicsUpdate()
{
	//Update positoin from rigidbody positoin
	transform_.setPosition( rigidBody_.getBulletPosition() );

	//Update Camera and listener position
	camera_->update(transform_, cameraOffset_);
	spty::SoundDevice::get()->setLocation(transform_.getPosition());

	//Update gun position, pitch and yaw
	glm::vec3 gunPos = transform_.getPosition();
	gunPos += camera_->getFront() * 0.2f;
	gunPos += camera_->getUp() * 0.01f;
	gunPos += transform_.getRight() * 0.2f;
	gun_->transform_.setPosition( gunPos );

	gun_->transform_.setPitch(transform_.getPitch());
	gun_->transform_.setYaw(transform_.getYaw() - 180.0f);

}

//Process the input for player controls
void Player::processInput(float& deltaTime)
{
	using namespace spty;

	//Temporary variables
	glm::vec3 direction = rigidBody_.getBulletInertia();
	glm::vec3 front = transform_.getFront();
	front = glm::normalize(glm::vec3(front.x, 0.0f, front.z));
	glm::vec3 right = transform_.getRight();
	right = glm::normalize(glm::vec3(right.x, 0.0f, right.z));

	float velocity = speed_ * deltaTime;

	//Left shift is sprint key
	if (Input::isKeyPressed(KeyCode::LeftShift))
		velocity *= 1.6f;

	//Move based on the keys W, A, S, & D
	if (Input::isKeyPressed(KeyCode::W))
		direction += front;
	if (Input::isKeyPressed(KeyCode::S))
		direction -= front;
	if (Input::isKeyPressed(KeyCode::D))
		direction += right;
	if (Input::isKeyPressed(KeyCode::A))
		direction -= right;

	glm::normalize(direction);
	direction *= velocity;

	if (Input::isKeyPressed(KeyCode::Space) && onGround())
		direction += WorldDir::UP * jumpHeight_ * deltaTime;

	rigidBody_.move(direction);

	//Fire weapon when mouse button is pressed
	if (Input::isButtonPressed(MouseCode::LeftButton))
		gun_->fire();
	else
	{
		AssaultRifle* AR = dynamic_cast<AssaultRifle*>(gun_);
		AR->hasFired_ = false;
	}

	if (Input::isKeyPressed(KeyCode::R))
		gun_->reload();

	glm::vec2 mouseOffset = Input::getCursorOffset();

	transform_.setAngularVelocity(mouseOffset.x * deltaTime);
	transform_.yaw(mouseOffset.x);
	transform_.pitch(mouseOffset.y);
}
