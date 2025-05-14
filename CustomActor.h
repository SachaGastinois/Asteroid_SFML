#pragma once
#include "MeshActor.h"
#include "CollisionComponent.h"

class CustomActor : public AMeshActor
{
	UCollisionComponent* collision;

public:
	CustomActor(Level* _level, const string& _name = "MeshActor");

};

