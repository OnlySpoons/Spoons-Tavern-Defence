#include "Actor.h"

namespace spty {

	//Constructor
	Actor::Actor(const Transform& data,
		Camera* camera,
		const std::string& modelPath)
		: GameObject(data, true),
		model_(modelPath == "" ? Model() : Model(modelPath)),
		camera_(camera),
		rigidBody_(transform_, new CapsuleCollider(transform_.getScale().x, transform_.getScale().y))
	{
	}

	//Destructor
	Actor::~Actor()
	{
		delete camera_;
	}

	//Render the object
	void Actor::draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass)
	{
		if (!isEnabled_) return;

		shader.use();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);

		model = transform_.getMatrix();

		model_.draw(shader, model);
	}

	bool Actor::onGround() const
	{
		RayCallback rayData = Physics::Raycast(transform_.getPosition(), WorldDir::DOWN * 100.0f);

		if (!rayData.hasHit()) return false;

		glm::vec3 distVec = Physics::btVector3ToglmVec3(rayData.m_hitPointWorld) - transform_.getPosition();

		float dist = abs(distVec.y);
		float height = transform_.getScale().y / 2;

		if (dist > height) return false;

		return true;
	}
}