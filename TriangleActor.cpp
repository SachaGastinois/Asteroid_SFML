#include "TriangleActor.h"

ATriangleActor::ATriangleActor(Level* _level, const float _radius, const string& _path, const IntRect& _rect)
						   : AMeshActor(_level, CircleShapeData(_radius, _path, _rect, 3))
{

}

ATriangleActor::ATriangleActor(const ATriangleActor& _other) : AMeshActor(_other)
{

}