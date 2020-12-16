#pragma once
#include "GameObject.h"
#include "Shader.h"
#include "Camera.h"
#include "Model.h"

namespace Spoonity {

	//Abstraction for possible directions of movement
	enum class Movement {
		FORWARD,
		BACKWARD,
		LEFT,
		RIGHT
	};

	class Actor : public GameObject
	{

	//Member variables
	public:
		Camera* _Camera;

		float _MouseSensitivity;
		float _FOV;

	protected:
		Model _Model;

	//Fuctions
	public:

		//Constructor
		Actor(const ObjectData& data,
			  Camera* camera,
			  const std::string& modelPath = "",
			  const Shader&	shader = Shader()
		);

		//Destructor
		virtual ~Actor();

		//Render the object
		virtual void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model) = 0;

		//Update the object
		virtual void update(float& deltaTime);

		//TODO: Remove all of this when input is abstracted

		//Processes the keyboard input to control camera movement
		virtual void ProcessKeyboard(Spoonity::Movement direction, float deltaTime, bool isSprinting) = 0;

		//Processes the mouse movement to control where the camera is facing
		virtual void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true) = 0;

		//Processes the scroll wheel to control the zoom
		virtual void ProcessMouseScroll(float yOffset) = 0;
	};
}