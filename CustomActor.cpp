#include "CustomActor.h"

CustomActor::CustomActor(Level* _level, const string& _name) : AMeshActor(_level, RectangleShapeData(Vector2f(50.0f,50.0f)), _name)
{
	collision = CreateDefaultSubobject<UCollisionComponent>();
	collision->SetInformation("UFO", IS_ALL, CT_BLOCK);
	collision->AddResponses({ {"UFO", CT_OVERLAP} });
	collision->GetBounds()->SetBoundsData(new RectangleBoundsData(GetLocation(), {50.0f, 50.0f}, degrees(0.0f)));

	mesh->SetOriginAtMiddle();
}