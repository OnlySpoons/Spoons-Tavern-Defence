#pragma once
#include <vector>

#include "GameObject.h"

namespace spty {

	class Scene
	{
		//Variables
	private:
		std::vector<GameObject*> _sceneObjects;

		//Functions
	public:

		//Constructor
		Scene();

		virtual ~Scene();

		//Draw the objects in the scene
		void draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass) const;

		//Update the objects in the scene
		void update(float& deltaTime) const;

		void physics() const;

		//Add object to the scene
		void addObject(GameObject* obj);

		//Remove object from scene
		bool removeObject(GameObject* obj);

		//Enable object in scene
		void enableObject(GameObject* obj);

		//Diable object in scene
		void disableObject(GameObject* obj);
	};
}