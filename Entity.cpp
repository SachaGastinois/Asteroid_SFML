#include "Entity.h"
#include "StaticMeshComponent.h"
#include "PlayerMovementComponent.h"
#include "CollisionComponent.h"
#include "AnimationComponent.h"
#include "CameraComponent.h"
#include "Bounds.h"
#include "Level.h"

AEntity::AEntity(Level* _level, const int _point, const FEntityData& _data, const string& _name, const TransformData& _transform)
	: AActor(_level, _name, _transform)
{
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(RectangleShapeData(
		_data.meshSize, _data.meshPath, PNG));
	if(_data.hitBoxType == EHitBoxType::HBT_CIRCLE)
	{
		hitBoxMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(CircleShapeData(
			_data.hitBoxRadius, "Utility/Transparent"));
	}
	else if(_data.hitBoxType == EHitBoxType::HBT_RECTANGLE)
	{
		hitBoxMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(RectangleShapeData(
			_data.hitBoxSize, "Utility/Transparent", PNG));
	}
	animationComponent = CreateDefaultSubobject<UAnimationComponent>();
	collisionComponent = CreateDefaultSubobject<UCollisionComponent>(hitBoxMeshComponent, "Asteroid", IS_ALL, CT_BLOCK);
	lifeComponent = CreateDefaultSubobject<ULifeComponent>(_data.lifeData);

	meshComponent->SetupAttachment(root);
	hitBoxMeshComponent->SetupAttachment(root);
	animationComponent->SetupAttachment(root);

	point = _point;
}

AEntity::AEntity(const AEntity& _other) : AActor(_other)
{
	meshComponent = _other.meshComponent;
	hitBoxMeshComponent = _other.hitBoxMeshComponent;
	animationComponent = _other.animationComponent;
	collisionComponent = _other.collisionComponent;

	animations = _other.animations;
	spriteSize = _other.spriteSize;
}

void AEntity::Construct()
{
	Super::Construct();
}

void AEntity::Deconstruct()
{
	Super::Deconstruct();
}

void AEntity::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void AEntity::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void AEntity::BeginDestroy()
{
	Super::BeginDestroy();
}

void AEntity::Init()
{
	meshComponent->SetOriginAtMiddle();

	SetupCollisions();
}

void AEntity::SetupCollisions()
{
	const ShapeObjectData& _shapeData = hitBoxMeshComponent->GetShape()->GetData();
	const ShapeObjectType& _shapeType = _shapeData.type;

	if (_shapeType == ShapeObjectType::SOT_CIRCLE)
	{
		collisionComponent->GetBounds()->SetBoundsData(new CircleBoundsData(_shapeData.data.circleData->radius, GetLocation()));
	}
	else if (_shapeType == ShapeObjectType::SOT_RECTANGLE)
	{
		collisionComponent->GetBounds()->SetBoundsData(new RectangleBoundsData(GetLocation(), _shapeData.data.rectangleData->size, GetRotation()));
	}
}

void AEntity::OnDeath()
{
	SetToDelete();
}
