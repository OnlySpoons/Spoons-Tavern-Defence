#include "Actor.h"

namespace spty {

	//Constructor
	Actor::Actor(const Transform& data,
		Camera* camera,
		const std::string& modelPath)
		: GameObject(data, true),
		_model(modelPath == "" ? Model() : Model(modelPath)),
		_camera(camera),
		_rigidBody(_transform, new BoxCollider(_transform.getScale()))
	{
	}

	//Destructor
	Actor::~Actor()
	{
		delete _camera;
	}
}