#include "Projectile.h"
#include "StaticMeshComponent.h"
#include "PlayerMovementComponent.h"
#include "CollisionComponent.h"
#include "AnimationComponent.h"
#include "CameraComponent.h"
#include "CollisionComponent.h"
#include "Bounds.h"
#include "Level.h"
#include "UFO.h"
#include "PlayerPawn.h"
#include "Asteroid.h"
#include "GameplayLevel.h"
#include "ClassicModeLevel.h"

AProjectile::AProjectile(Level* _level, const string& _spriteSheetPath, const bool _isPlayerProjectile, 
	const string& _name, const TransformData& _transform) 
	: AEntity(_level, 0, FEntityData({ 30.0f, 28.0f }, 15.0f, _spriteSheetPath,
	  FLifeData(1, 1, [&]() { OnDeath(); })), _name, _transform)
{
	speed = 500.0f;
	isPlayerProjectile = _isPlayerProjectile;
}

AProjectile::AProjectile(const AProjectile& _other) : AEntity(_other)
{
	speed = _other.speed;
	isPlayerProjectile = _other.isPlayerProjectile;
}

void AProjectile::Construct()
{
	Super::Construct();
}

void AProjectile::Deconstruct()
{
	Super::Deconstruct();
}

void AProjectile::BeginPlay()
{
	SetLifeSpan(5.0f);

	Super::BeginPlay();

	Init();
}

void AProjectile::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	Move(_deltaTime);
}

void AProjectile::BeginDestroy()
{
	Super::BeginDestroy();
}

void AProjectile::Init()
{
	spriteSize = { 64, 64 };

	SetZOrder(3);
	GetLevel()->GetCameraManager().SetZOrder(meshComponent->GetRenderMeshToken(), zOrder);

	SetupAnimations();
}

void AProjectile::SetupAnimations()
{

	vector<SpriteData> _animationSpritesData;

	for (int _i = 0; _i < 7; _i++)
	{
		for (int _j = 0; _j < 9; _j++)
		{
			if (_i >= 5 && _j >= 8) continue;
			SpriteData _data = SpriteData({ spriteSize.x * _i, spriteSize.y * _j }, spriteSize);
			_animationSpritesData.push_back(_data);
		}
	}
	Animation* _anim = animationComponent->AddAnimation(_animationSpritesData, 3.0f, "Movement", meshComponent->GetShape());
	animations.insert(pair<string, Animation*>("Movement", _anim));
	animationComponent->SetCurrentAnimation(animations["Movement"]);
	animationComponent->StartAnimation();
}

void AProjectile::SetupCollisions()
{
	Super::SetupCollisions();

	collisionComponent->SetInformation("Projectile", IS_ALL, CT_BLOCK);
	collisionComponent->AddResponses({ {"Player", CT_BLOCK} });
	collisionComponent->AddResponses({ {"UFO", CT_BLOCK} });
	collisionComponent->AddResponses({ {"Asteroid", CT_BLOCK} });
	collisionComponent->AddResponses({ {"Projectile", CT_NONE} });
}

void AProjectile::Move(const float _deltaTime)
{
	const Vector2f& _newLoc = GetLocation() + GetForwardVector() * speed * _deltaTime;
	SetLocation(_newLoc);
}

void AProjectile::OnDeath()
{
	Super::OnDeath();
}

void AProjectile::CollisionEnter(const CollisionData& _data)
{
	Super::CollisionEnter(_data);

 	if (_data.channelName == "Asteroid")
	{
		if (AAsteroid* _asteroid = Cast<AAsteroid>(_data.other))
		{
			if (!isPlayerProjectile) return;

			_asteroid->GetLife()->RemoveLife();
			if (UGameplayLevel* _level = Cast<UGameplayLevel>(GetLevel()))
			{
				_level->AddPoints(_asteroid->GetPoint());
			}
		}
	}
	else if (_data.channelName == "Player")
	{
		if (APlayerPawn* _player = Cast<APlayerPawn>(_data.other))
		{
			if (isPlayerProjectile) return;

			_player->GetLife()->RemoveLife();
		}
	}
	else if (_data.channelName == "UFO")
	{
		if (AUFO* _ufo = Cast<AUFO>(_data.other))
		{
			if (!isPlayerProjectile) return;

			_ufo->GetLife()->RemoveLife();
			if (UGameplayLevel* _level = Cast<UGameplayLevel>(GetLevel()))
			{
				_level->AddPoints(_ufo->GetPoint());
			}
		}
	}

	//LOG(Warning, "CollisionEnter");
}
