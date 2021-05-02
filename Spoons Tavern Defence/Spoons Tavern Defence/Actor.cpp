#include "Actor.h"

namespace spty {

	//Constructor
	Actor::Actor(const Transform& data,
		Camera* camera,
		const std::string& modelPath)
		: GameObject(data, true),
		_model(modelPath == "" ? Model() : Model(modelPath)),
		_camera(camera),
		_rigidBody(_transform, new CapsuleCollider(_transform.getScale().x, _transform.getScale().y))
	{
	}

	//Destructor
	Actor::~Actor()
	{
		delete _camera;
	}

	//Render the object
	void Actor::draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass)
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

	bool Actor::onGround()
	{
		float height = _transform.getScale().y / 2;
		float offset = 0.0f;

		glm::vec3 collisionPoint = WorldDir::DOWN * 100.0f;

		RayCallback rayData = Physics::Raycast(_transform.getPosition(), collisionPoint);

		if (rayData.hasHit())
		{
			glm::vec3 distVec = Physics::btVector3ToglmVec3(rayData.m_hitPointWorld) - _transform.getPosition();

			float dist = abs(distVec.y);

			if (dist < height + offset)
			{
				return true;
			}
		}

		return false;
	}
}