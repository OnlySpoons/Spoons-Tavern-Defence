#include "Scene.h"

namespace spty {

	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
		for (auto it = sceneObjects_.begin(); it < sceneObjects_.end(); ++it)
		{
			delete *it;
		}

		sceneObjects_.clear();
	}

	void Scene::draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass) const
	{
		for (GameObject* obj : sceneObjects_)
		{
			obj->draw(shader, projection, view, model, pass);
		}
	}

	void Scene::update(float& deltaTime) const
	{
		for (GameObject* obj : sceneObjects_)
		{
			obj->update(deltaTime);
		}
	}

	void Scene::physicsUpdate() const
	{
		for (GameObject* obj : sceneObjects_)
		{
			obj->physicsUpdate();
		}
	}

	void Scene::addObject(GameObject* obj)
	{
		sceneObjects_.emplace_back(std::move(obj));
	}

	bool Scene::removeObject(GameObject* obj)
	{
		auto it = std::find(sceneObjects_.begin(), sceneObjects_.end(), obj);
		
		if (it == sceneObjects_.end()) return false;

		sceneObjects_.erase(it);
		return true;
	}

	void Scene::enableObject(GameObject* obj)
	{
		auto it = std::find(sceneObjects_.begin(), sceneObjects_.end(), obj);

		if (it == sceneObjects_.end()) return;

		obj->enable();
	}

	void Scene::disableObject(GameObject* obj)
	{
		auto it = std::find(sceneObjects_.begin(), sceneObjects_.end(), obj);

		if (it == sceneObjects_.end()) return;

		obj->disable();
	}
}