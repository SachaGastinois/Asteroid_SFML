#include "RectangleActor.h"

ARectangleActor::ARectangleActor(Level* _level, const RectangleShapeData& _data) : AMeshActor(_level, _data)
{

}

ARectangleActor::ARectangleActor(const ARectangleActor& _other) : AMeshActor(_other)
{

}