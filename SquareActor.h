#pragma once
#include "RectangleActor.h"

class ASquareActor : public ARectangleActor
{
public:
	ASquareActor(Level* _level, const float _size, const string& _path = "", const TextureExtensionType& _textureType = PNG, const IntRect& _rect = {});
	ASquareActor(const ASquareActor& _other);
};