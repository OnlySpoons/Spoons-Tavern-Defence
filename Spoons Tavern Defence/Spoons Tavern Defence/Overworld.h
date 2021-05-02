#pragma once
#include "Scene.h"

#include "GameObject.h"
#include "Skybox.h"
#include "PhysicsEntity.h"

class Overworld : public spty::Scene
{
public:
	spty::Model* _worldModel;

	Overworld();

	virtual ~Overworld() {}
};