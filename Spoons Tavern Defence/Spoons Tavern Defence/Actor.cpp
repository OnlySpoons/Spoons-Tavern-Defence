#include "Actor.h"

namespace Spoonity {

	//Constructor
	Actor::Actor(const ObjectData& data,
				 Camera* camera,
				 const std::string& modelPath,
				 const Shader& shader)
		: GameObject(data, shader, true),
		_Model(modelPath == "" ? Model() : Model(modelPath)),
		_Camera(camera)
	{
	}

	//Destructor
	Actor::~Actor()
	{
		delete _Camera;
	}

	//Update the object
	void Actor::update(float& deltaTime)
	{
		_Camera->_Position = _Data.position + glm::vec3(0.0f, 0.2f, 0.0f);
	}
}