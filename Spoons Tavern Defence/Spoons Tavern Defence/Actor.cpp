#include "Actor.h"

namespace Spoonity {

	//Constructor
	Actor::Actor(const Transform& data,
		Camera* camera,
		const std::string& modelPath)
		: GameObject(data, true),
		_model(modelPath == "" ? Model() : Model(modelPath)),
		_camera(camera)
	{
	}

	//Destructor
	Actor::~Actor()
	{
		delete _camera;
	}
}