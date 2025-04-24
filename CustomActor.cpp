#include "CustomActor.h"

CustomActor::CustomActor(Level* _level, const string& _name) : AActor(_level, _name)
{
	collision = CreateDefaultSubobject<UCollisionComponent>();
	collision->SetInformation("ActorCollision", IS_ALL, CT_BLOCK);
	collision->AddResponses({ {"test-movement", CT_OVERLAP} });
	collision->GetBounds()->SetBoundsData(new RectangleBoundsData({500.0f, 500.0f }, { 100.0f, 100.0f }, degrees(0.0f)));
}