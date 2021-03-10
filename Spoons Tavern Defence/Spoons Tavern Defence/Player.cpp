#include "Player.h"

//Constructor
Player::Player(const Spoonity::Transform& transform,
	const std::string& modelPath)
	: Actor(transform, new Spoonity::Camera(), modelPath),
	_cameraOffset(glm::vec3(0.0f, 0.2f, 0.0f)),
	_speed(2.0f)
{
	_transform.setPosition(glm::vec3(0.0f, 0.5f, 0.0f));

	_transform.setRotation(glm::vec3(0.0f, 0.0f, 0.0f));

	_transform.setScale(glm::vec3(1.0f));

	_camera->update(_transform, _cameraOffset);
}

//Render the player Model
void Player::draw(const Spoonity::Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, Spoonity::PassType pass)
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

//Process the input for player controls
void Player::processInput(float& deltaTime)
{
	using namespace Spoonity;

	//Escape closes the window
	if (Input::isKeyPressed(KeyCode::Escape))
		Input::closeWindow();

	//Temporary variables
	float velocity = _speed * deltaTime;

	glm::vec3 front = _transform.getFront();
	front = glm::normalize(glm::vec3(front.x, 0.0f, front.z));

	glm::vec3 right = _transform.getRight();
	right = glm::normalize(glm::vec3(right.x, 0.0f, right.z));

	//Left shift is sprint key
	if (Input::isKeyPressed(KeyCode::LeftShift))
		velocity *= 1.6f;

	//Set the new position of the camera based on the keys W, A, S, & D
	if (Input::isKeyPressed(KeyCode::W))
		_transform.move(front * velocity);
	if (Input::isKeyPressed(KeyCode::S))
		_transform.move(-front * velocity);
	if (Input::isKeyPressed(KeyCode::D))
		_transform.move(right * velocity);
	if (Input::isKeyPressed(KeyCode::A))
		_transform.move(-right * velocity);

	
	////Flight controls
	//if (Input::isKeyPressed(KeyCode::Space))
	//	_transform.move(WorldDir::UP * velocity);
	//if (Input::isKeyPressed(KeyCode::LeftControl))
	//	_transform.move(WorldDir::DOWN * velocity);

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