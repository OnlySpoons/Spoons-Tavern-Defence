#include "Scene.h"

namespace spty {

	//Constructor
	Scene::Scene(int id)
		: _id(id)
	{
	}

	Scene::~Scene()
	{
		for (auto it = _sceneObjects.begin(); it < _sceneObjects.end(); ++it)
		{
			delete* it;
		}

		_sceneObjects.clear();
	}

	//Draw the objects in the scene
	void Scene::draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass) const
	{
		for (GameObject* obj : _sceneObjects)
		{
			obj->draw(shader, projection, view, model, pass);
		}
	}

	//Update the objects in the scene
	void Scene::update(float& deltaTime) const
	{
		for (GameObject* obj : _sceneObjects)
		{
			obj->update(deltaTime);
		}
	}

	//Update the physics of objects in the scene
	void Scene::physics() const
	{
		for (GameObject* obj : _sceneObjects)
		{
			obj->physicsUpdate();
		}
	}

	//Add object to the scene
	void Scene::addObject(GameObject* obj)
	{
		//Add the object to the list of objects in the scene
		_sceneObjects.emplace_back(std::move(obj));
	}

	//Remove object to the scene
	bool Scene::removeObject(GameObject* obj)
	{
		//Find position of the object
		auto it = std::find(_sceneObjects.begin(), _sceneObjects.end(), obj);

		//Check if the object was found
		if (it != _sceneObjects.end())
		{
			//Erase the object
			_sceneObjects.erase(it);
			return true;
		}

		//Return false if the object wasn't erased
		return false;
	}
	void Scene::enableObject(GameObject* obj)
	{
		auto it = std::find(_sceneObjects.begin(), _sceneObjects.end(), obj);

		if (it != _sceneObjects.end())
		{
			obj->enable();
		}
	}

	void Scene::disableObject(GameObject* obj)
	{
		auto it = std::find(_sceneObjects.begin(), _sceneObjects.end(), obj);

		if (it != _sceneObjects.end())
		{
			obj->disable();
		}
	}
}