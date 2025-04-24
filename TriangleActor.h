#pragma once
#include "MeshActor.h"

class ATriangleActor : public AMeshActor
{
public:
	ATriangleActor(Level* _level, const float _radius, const string& _path = "", const IntRect& _rect = {});
	ATriangleActor(const ATriangleActor& _other);
};