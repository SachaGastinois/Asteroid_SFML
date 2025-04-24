#include "SquareActor.h"

ASquareActor::ASquareActor(Level* _level, const float _size, const string& _path, const TextureExtensionType& _textureType, const IntRect& _rect)
					   : ARectangleActor(_level, RectangleShapeData(Vector2f(_size, _size), _path, _textureType, false, _rect))
{

}

ASquareActor::ASquareActor(const ASquareActor& _other) : ARectangleActor(_other)
{

}