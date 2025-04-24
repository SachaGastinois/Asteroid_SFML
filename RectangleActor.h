#pragma once
#include "MeshActor.h"

class ARectangleActor : public AMeshActor
{
public:
	ARectangleActor(Level* _level, const RectangleShapeData& _data);
	ARectangleActor(const ARectangleActor& _other);
};