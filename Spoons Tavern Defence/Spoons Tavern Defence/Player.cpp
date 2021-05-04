#include "Player.h"

//Constructor
Player::Player(Weapon* gun,
	const spty::Transform& transform,
	const std::string& modelPath
)
	: Actor(transform, new spty::Camera(), modelPath),
	_gun(gun),
	_soundPlayer(new spty::SoundEffectsPlayer()),
	_hurtSound(spty::SoundEffectsLibrary::load("Data/Sounds/Serious/playerHurt.ogg")),
	_deathSound(spty::SoundEffectsLibrary::load("Data/Sounds/Serious/playerDeath.ogg"))
{
	_cameraOffset = glm::vec3(0.0f, 0.3f, 0.0f);

	_camera->update(_transform, _cameraOffset);

	_rigidBody.setMass(150.0f);

	_gun->enable();

	_speed = 70.0f;
	_jumpHeight = 70.0f;
	_jumping = false;

	//Handle DamageEvents
	spty::Dispatcher<GameEventType>::subscribe(PlayerDamageEvent::Type,
		[&](spty::Event<GameEventType>& e)
		{
			PlayerDamageEvent damage = spty::EventCast<PlayerDamageEvent>(e);

			if (_health > 0)
			{
				_soundPlayer->Play(_hurtSound);
				_health -= damage.amount;
				_rigidBody.move(damage.direction * 2.5f);
			}
			e.handle();
		}
	);

	spty::SoundDevice::get()->SetAttunation(AL_INVERSE_DISTANCE_CLAMPED);
	spty::SoundDevice::get()->SetGain(0.1f);
}

Player::~Player()
{
	delete _soundPlayer;
	spty::SoundEffectsLibrary::unLoad(_hurtSound);
	spty::SoundEffectsLibrary::unLoad(_deathSound);
}

//Update the player
void Player::update(float& deltaTime)
{
	if (_health > 0)
	{
		processInput(deltaTime);

		if (onGround())
			_rigidBody.disableGravity();
		else
			_rigidBody.enableGravity();
	}
	else
	{
		static bool died = true;
		if (died)
		{
			died = false;
			_soundPlayer->Play(_deathSound);
		}
	}

	//Escape closes the window
	if (spty::Input::isKeyPressed(spty::KeyCode::Escape))
		spty::Input::closeWindow();
}

void Player::physicsUpdate()
{
	_transform.setPosition( _rigidBody.getBulletPosition() );
	//_transform.setRotation( _rigidBody.getBulletRotation() );

	//Update Cameraand listener position
	_camera->update(_transform, _cameraOffset);
	spty::SoundDevice::get()->SetLocation(_transform.getPosition());
	//spty::SoundDevice::get()->SetOrientation(-_transform.getFront(), -_transform.getUp());

	glm::vec3 gunPos = _transform.getPosition();
	gunPos += _camera->getFront() * 0.2f;
	gunPos += _camera->getUp() * 0.01f;
	gunPos += _transform.getRight() * 0.2f;

	float pitch = _transform.getPitch();
	float pitchConstraint = 60.0f;

	/*if (abs(pitch) > pitchConstraint)
		gunPos += _transform.getRight() * 0.3f;*/

	_gun->_transform.setPitch( pitch );
	_gun->_transform.setYaw(_transform.getYaw() - 180.0f);

	_gun->_transform.setPosition( gunPos );
}

//Process the input for player controls
void Player::processInput(float& deltaTime)
{
	using namespace spty;

	//Position Selecting utility button
	/*if (Input::isButtonPressed(MouseCode::RightButton))
	{
		glm::vec3 pos = _transform.getPosition();
		std::cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	}*/

	//Temporary variables
	glm::vec3 direction = _rigidBody.getBulletInertia();

	glm::vec3 front = _transform.getFront();
	front = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

	glm::vec3 right = _transform.getRight();
	right = glm::normalize(glm::vec3(right.x, 0.0f, right.z));

	float velocity = _speed * deltaTime;

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

	if (Input::isKeyPressed(KeyCode::Space))
	{
		if (onGround() && !_jumping)
		{
			direction += WorldDir::UP * _jumpHeight * deltaTime;
			_jumping = true;
		}
	}
	else
		_jumping = false;

	_rigidBody.move(direction);

	//Fire weapon when mouse button is pressed
	if (Input::isButtonPressed(MouseCode::LeftButton))
	{
		_gun->fire();
	}
	else
	{
		AssaultRifle* AR = dynamic_cast<AssaultRifle*>(_gun);
		AR->_firingEmpty = false;
	}

	if (Input::isKeyPressed(KeyCode::R))
	{
		_gun->reload();
	}

	glm::vec2 mouseOffset = Input::getCursorOffset();

	_transform.setAngularVelocity(mouseOffset.x * deltaTime);
	_transform.yaw(mouseOffset.x);
	_transform.pitch(mouseOffset.y);
}
