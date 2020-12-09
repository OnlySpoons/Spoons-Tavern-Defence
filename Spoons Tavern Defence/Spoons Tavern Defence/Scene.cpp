#include "Scene.h"

namespace GameEngine {

	//Constructor

	Scene::Scene(std::vector<GameObject*> &objs)
	{
		_SceneObjects = std::move(objs);
	}

	//Draw the objects in the scene
	void Scene::draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model) const
	{
		for (GameObject* obj : _SceneObjects)
		{
			obj->draw(projection, view, model);
		}
	}

	//Update the objects in the scene
	void Scene::update(float &deltaTime) const
	{
		for (GameObject* obj : _SceneObjects)
		{
			obj->update(deltaTime);
		}
	}

	//Add object to the scene
	void Scene::addObject(GameObject* obj)
	{
		//Add the object to the list of objects in the scene
		_SceneObjects.emplace_back(std::move(obj));
	}

	//Remove object to the scene
	bool Scene::removeObject(GameObject* obj)
	{
		//Find position of the object
		auto it = std::find(_SceneObjects.begin(), _SceneObjects.end(), obj);

		//Check if the object was found
		if (it != _SceneObjects.end())
		{
			//Erase the object
			_SceneObjects.erase(it);
			return true;
		}

		//Return false if the object wasn't erased
		return false;
	}
	void Scene::enableObject(GameObject* obj)
	{
		auto it = std::find(_SceneObjects.begin(), _SceneObjects.end(), obj);

		if (it != _SceneObjects.end())
		{
			obj->enable();
		}
	}

	void Scene::disableObject(GameObject* obj)
	{
		auto it = std::find(_SceneObjects.begin(), _SceneObjects.end(), obj);

		if (it != _SceneObjects.end())
		{
			obj->disable();
		}
	}
}