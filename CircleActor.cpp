#include "CircleActor.h"

ACircleActor::ACircleActor(Level* _level, const float _radius, const string& _path,
						 const IntRect& _rect, const size_t& _pointCount)
					   : AMeshActor(_level, CircleShapeData(_radius, _path, _rect, _pointCount))
{
	
}

ACircleActor::ACircleActor(const ACircleActor& _other) : AMeshActor(_other)
{

}