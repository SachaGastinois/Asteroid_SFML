#pragma once
#include "Actor.h"
#include "CollisionComponent.h"

class CustomActor : public AActor
{
	UCollisionComponent* collision;

public:
	CustomActor(Level* _level, const string& _name = "MeshActor");

};

