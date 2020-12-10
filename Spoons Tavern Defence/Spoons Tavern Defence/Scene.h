#pragma once
#include <vector>

#include "GameObject.h"

enum Level {
	Overworld = 0
};

namespace GameEngine {

	class Scene
	{
	//Variables
	public:
		Level _ID;

	private:
		std::vector<GameObject*> *_SceneObjects;

	//Functions
	public:

		//Constructor
		Scene() {}

		Scene(Level id, std::vector<GameObject*> *objs);

		~Scene();

		//Draw the objects in the scene
		void draw(glm::mat4 projection, glm::mat4 view, glm::mat4 model) const;

		//Update the objects in the scene
		void update(float &deltaTime) const;

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