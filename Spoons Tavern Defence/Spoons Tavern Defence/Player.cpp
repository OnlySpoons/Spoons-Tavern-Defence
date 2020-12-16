#include "Player.h"

//Constructor
Player::Player(const Spoonity::ObjectData& const data,
			   const std::string&		   const modelPath,
			   const Spoonity::Shader&	   const shader)
	: Actor(data, new Spoonity::Camera(data.position, data.direction), modelPath, shader)
{
}

//Render the player Model
void Player::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model)
{
	if (_IsEnabled)
	{
		_Shader.use();
		_Shader.setMat4("projection", projection);
		_Shader.setMat4("view", view);

		glm::vec3 lookPos = _Data.position + glm::vec3(_Data.direction.x, 0.0f, _Data.direction.z);

		model = glm::mat4(1.0f);
		model = glm::translate(model, _Data.position);
		model *= glm::lookAt(_Data.position, lookPos, Spoonity::Camera::_WorldUp);
		model = glm::scale(model, _Data.scale);

		_Model.draw(_Shader, &model);
	}
}

//Update the player
void Player::update(float& deltaTime)
{
	Actor::update(deltaTime);
}

//Processes the keyboard input to control camera movement
void Player::ProcessKeyboard(Spoonity::Movement direction, float deltaTime, bool isSprinting)
{
	//To prevent repetition
	using Movement = Spoonity::Movement;

	float velocity = _Data.speed * deltaTime;
	glm::vec3 front = glm::vec3(_Data.direction.x, 0.0f, _Data.direction.z);
	glm::vec3& right = _Camera->_Right;

	if (isSprinting)
		velocity *= 2;
	if (direction == Movement::FORWARD)
		_Data.position += front * velocity;
	if (direction == Movement::BACKWARD)
		_Data.position -= front * velocity;
	if (direction == Movement::RIGHT)
		_Data.position += right * velocity;
	if (direction == Movement::LEFT)
		_Data.position -= right * velocity;
}

//Processes the mouse movement to control where the camera is facing
void Player::ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch)
{
	xOffset *= _MouseSensitivity;
	yOffset *= _MouseSensitivity;

	_Camera->_Yaw += xOffset;
	_Camera->_Pitch += yOffset;

	if (constrainPitch)
	{
		if (_Camera->_Pitch > 89.0f)
			_Camera->_Pitch = 89.0f;
		if (_Camera->_Pitch < -89.0f)
			_Camera->_Pitch = -89.0f;
	}

	_Camera->updateCameraVectors();

	_Data.direction = _Camera->_Front;
}

//Processes the scroll wheel to control the zoom
void Player::ProcessMouseScroll(float yOffset)
{
	if (_FOV >= 1.0f && _FOV <= 45.0f)
		_FOV -= yOffset;
	if (_FOV < 1.0f)
		_FOV = 1.0f;
	if (_FOV > 45.0f)
		_FOV = 45.0f;
}