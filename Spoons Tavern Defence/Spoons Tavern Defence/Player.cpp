#include "Player.h"

//Constructor
Player::Player(const spty::Transform& transform,
	const std::string& modelPath)
	: Actor(transform, new spty::Camera(), modelPath),
	_cameraOffset(glm::vec3(0.0f, 0.2f, 0.0f)),
	_speed(70.0f)
{
	_transform.setPosition(glm::vec3(10.0f, 0.5f, 10.0f));

	_transform.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));

	_transform.setScale(glm::vec3(1.0f));

	_camera->update(_transform, _cameraOffset);

	_rigidBody.setMass(150.0f);
}

//Render the player Model
void Player::draw(const spty::Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, spty::PassType pass)
{
	if (_isEnabled)
	{
		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		model = _transform.getMatrix();

		_model.draw(shader, model);
	}

	
}

//Update the player
void Player::update(float& deltaTime)
{
	processInput(deltaTime);
}

void Player::physicsUpdate()
{
	_transform.setPosition( _rigidBody.getBulletPosition() );
	//_transform.setRotation( _rigidBody.getBulletRotation() );
}

//Process the input for player controls
void Player::processInput(float& deltaTime)
{
	using namespace spty;

	//Escape closes the window
	if (Input::isKeyPressed(KeyCode::Escape))
		Input::closeWindow();

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

	//direction = glm::vec3(direction.x, 0.0f, direction.z);

	_rigidBody.move(direction * velocity);
	
	////Flight controls
	//if (Input::isKeyPressed(KeyCode::Space))
	//	_rigidBody.move(WorldDir::UP * velocity);
	//if (Input::isKeyPressed(KeyCode::LeftControl))
	//	_rigidBody.move(WorldDir::DOWN * velocity);

	//Print player position when mouse button is pressed
	if (Input::isButtonPressed(MouseCode::LeftButton))
	{
		const glm::vec3& pos = _transform.getPosition();
		std::cout << "(" << pos.x << ", " << pos.y << ", " << pos.z << ")" << std::endl;
	}

	glm::vec2 mouseOffset = Input::getCursorOffset();

	_transform.yaw(mouseOffset.x);
	_transform.pitch(mouseOffset.y);

	//Update Camera
	_camera->update(_transform, _cameraOffset);
}