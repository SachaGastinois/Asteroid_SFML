#pragma once
#include "MeshActor.h"

class ACircleActor : public AMeshActor
{
public:
	ACircleActor(Level* _level, const float _radius, const string& _path = "", const IntRect& _rect = {},
				const size_t& _pointCount = 30);
	ACircleActor(const ACircleActor& _other);
};