#include "Player.h"

//Constructor
Player::Player(const Spoonity::ObjectData& data,
	const std::string& modelPath)
	: Actor(data, new Spoonity::Camera(data.position, data.front), modelPath)
{
	_data.position = glm::vec3(0.0f, 0.5f, 0.0f);
	_camera->_position = _data.position + glm::vec3(0.0f, 0.2f, 0.0f);

	_data.angle = glm::vec2(-90.0f, 0.0f);
	_camera->_yaw = _data.angle.x;
	_camera->_pitch = _data.angle.y;

	_data.front = _camera->_front;
	_data.front = _camera->_up;
	_data.updateVectors();

	_data.scale = glm::vec3(1.0f);
	_data.speed = 2.0f;

	_camera->updateCameraVectors();

	_firstMouse = true;
	_lastPos = glm::vec2(0.0f);
}

//Render the player Model
void Player::draw(const Spoonity::Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
	if (_isEnabled)
	{
		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		model = glm::mat4(1.0f);
		model = glm::translate(model, _data.position);
		model = glm::rotate(model, glm::radians(_data.angle.x), _data.up);
		model = glm::scale(model, _data.scale);

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
	float velocity = _data.speed * deltaTime;
	glm::vec3 front = glm::normalize(glm::vec3(_data.front.x, 0.0f, _data.front.z));
	glm::vec3& right = _camera->_right;

	//Left shift is sprint key
	if (Input::isKeyPressed(KeyCode::LeftShift))
		velocity *= 1.6f;

	//Set the new position of the camera based on the keys W, A, S, & D
	if (Input::isKeyPressed(KeyCode::W))
		_camera->_position += front * velocity;
	if (Input::isKeyPressed(KeyCode::S))
		_camera->_position -= front * velocity;
	if (Input::isKeyPressed(KeyCode::D))
		_camera->_position += right * velocity;
	if (Input::isKeyPressed(KeyCode::A))
		_camera->_position -= right * velocity;

	/*
	//Flight controls
	if (Input::isKeyPressed(KeyCode::Space))
		_camera->_position += _camera->WorldUp * velocity;
	if (Input::isKeyPressed(KeyCode::LeftControl))
		_camera->_position -= _camera->WorldUp * velocity;

	//Clamp Height
	if (_camera->_position.y < 0.7f)
		_camera->_position.y = 0.7f;
	*/

	//Update the player position based on camera position
	_data.position = _camera->_position - glm::vec3(0.0f, 0.2f, 0.0f);

	//Print player position when mouse button is pressed
	if (Input::isButtonPressed(MouseCode::LeftButton))
		std::cout << "(" << _data.position.x << ", " << _data.position.y << ", " << _data.position.z << ")" << std::endl;

	glm::vec2 mousePosition = Input::getCursorPos();

	if (_firstMouse)
	{
		_lastPos = mousePosition;
		_firstMouse = false;
	}

	float xOffset = mousePosition.x - _lastPos.x;
	float yOffset = _lastPos.y - mousePosition.y; //Reversed since y-coordinates go from bottom to top

	_lastPos = mousePosition;

	xOffset *= 0.1f;
	yOffset *= 0.1f;

	_camera->_yaw += xOffset;
	_camera->_pitch += yOffset;

	if (_camera->_pitch > 89.0f)
		_camera->_pitch = 89.0f;
	if (_camera->_pitch < -89.0f)
		_camera->_pitch = -89.0f;

	_camera->updateCameraVectors();

	_data.front = _camera->_front;
	_data.updateVectors();

	_data.angle.x = _camera->_yaw;
	_data.angle.y = _camera->_pitch;
}