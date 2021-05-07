#pragma once
/*
Group Name: OnlySpoons

Members: Martin Harvey(B00329330), Thomas Cole(B00269678) & Harry Durham(B00347454)

We declare that the following code was produced by OnlySpoons as a group assignment for the CGT Group Project module and that it is our own work.

We are aware of the penalties incurred by submitting in full or in part work that is not our own and that was developed by third parties that are not appropriately acknowledged.
*/
#include <vector>

#include "GameObject.h"

namespace spty {
	class Scene
	{
	//Variables
	private:
		std::vector<GameObject*> sceneObjects_;

	//Functions
	public:
		//Constructor
		Scene();

		//Destructor
		virtual ~Scene();

		void draw(const Shader& shader, glm::mat4 projection, glm::mat4 view, glm::mat4 model, PassType pass) const;

		void update(float& deltaTime) const;
		void physicsUpdate() const;

		void addObject(GameObject* obj);
		bool removeObject(GameObject* obj);

		void enableObject(GameObject* obj);
		void disableObject(GameObject* obj);
	};
}