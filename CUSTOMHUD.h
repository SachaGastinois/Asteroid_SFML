#pragma once

#include "HUD.h"
#include "MeshActor.h"

using namespace UI;

class CUSTOMHUD : public HUD
{
	AMeshActor* mesh;
public:
	CUSTOMHUD(Level* _level);
	CUSTOMHUD(const CUSTOMHUD& _other);
};

