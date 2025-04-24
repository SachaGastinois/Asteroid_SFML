#include "MeshActor.h"
#include "CameraManager.h"
#include "CollisionManager.h"
#include "Level.h"

AMeshActor::AMeshActor(Level* _level, const CircleShapeData& _data, const string& _name) : AActor(_level, _name)
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(_data);
}

AMeshActor::AMeshActor(Level* _level, const RectangleShapeData& _data, const string& _name) : AActor(_level, _name)
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(_data);
}

AMeshActor::AMeshActor(const AMeshActor& _other) : AActor(_other)
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(*_other.mesh);
}


void AMeshActor::SetZOrder(const int _zOrder)
{
	Super::SetZOrder(_zOrder);

	GetLevel()->GetCameraManager().SetZOrder(mesh->GetRenderMeshToken(), zOrder);
}