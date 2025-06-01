#include "UFO.h"
#include "StaticMeshComponent.h"
#include "PlayerMovementComponent.h"
#include "CollisionComponent.h"
#include "AnimationComponent.h"
#include "CameraComponent.h"
#include "ShootComponent.h"
#include "CollisionComponent.h"
#include "Bounds.h"
#include "Level.h"
#include "Projectile.h"
#include "PlayerPawn.h"
#include "TimerManager.h"
#include "GameplayLevel.h"

AUFO::AUFO(Level* _level, const string& _meshPath, const string& _name, const TransformData& _transform) 
	: AEntity(_level, 300, FEntityData(Vector2f(50.0f, 50.0f), 25.0f, _meshPath,
		FLifeData(1, 1, [&]() { OnDeath(); })), _name, _transform)
{
	shootComponent = CreateDefaultSubobject<UShootComponent>();

	speed = 100.0f;
	direction = Vector2f();

	shootTimer = 2.5f;
	currentShootTime = 2.5f;
	directionTimer = 5.0f;
	currentDirectionTime = 5.0f;
}

AUFO::AUFO(const AUFO& _other) : AEntity(_other)
{
	speed = _other.speed;
	direction = _other.direction;

	shootTimer = _other.shootTimer;
	directionTimer = _other.directionTimer;
}

void AUFO::Construct()
{
	Super::Construct();
}

void AUFO::Deconstruct()
{
	Super::Deconstruct();
}

void AUFO::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void AUFO::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	Move(_deltaTime);

	UpdateShootTime(_deltaTime);
	UpdateDirectionTime(_deltaTime);
}

void AUFO::BeginDestroy()
{
	Super::BeginDestroy();
}


void AUFO::Init()
{
	spriteSize = { 32, 32 };

	SetZOrder(1);
	GetLevel()->GetCameraManager().SetZOrder(meshComponent->GetRenderMeshToken(), zOrder);

	SetupAnimations();

	SetupSocket();

}

void AUFO::SetupSocket()
{
	vector<FSocketData> _sockets;

	const vector<Vector2f>& _relativeLocs =
	{
		{ 0.0f, 0.0f },
	};

	const int _size = static_cast<int>(_relativeLocs.size());
	for (int _index = 0; _index < _size; _index++)
	{
		AActor* _socket = GetLevel()->SpawnActor<AActor>("Socket");
		_sockets.push_back(FSocketData(_socket, _relativeLocs[_index]));
	}

	_sockets[0].isActive = true;

	shootComponent->SetSockets(_sockets);
}

void AUFO::SetupAnimations()
{
	vector<SpriteData> _animationSpritesData;

	for (int _i = 0; _i < 4; _i++)
	{
		SpriteData _data = SpriteData({ spriteSize.x * _i, 0 }, spriteSize);
		_animationSpritesData.push_back(_data);
	}
	Animation* _anim = animationComponent->AddAnimation(_animationSpritesData, 0.5f, "Movement", meshComponent->GetShape());
	animations.insert(pair<string, Animation*>("Movement", _anim));
	animationComponent->SetCurrentAnimation(animations["Movement"]);
	animationComponent->StartAnimation();
}

void AUFO::SetupCollisions()
{
	Super::SetupCollisions();

	collisionComponent->SetInformation("UFO", IS_ALL, CT_BLOCK);
	collisionComponent->AddResponses({ {"Player", CT_BLOCK} });
	collisionComponent->AddResponses({ {"UFO", CT_NONE} });
	collisionComponent->AddResponses({ {"Asteroid", CT_NONE} });
	collisionComponent->AddResponses({ {"Projectile", CT_BLOCK} });
}

void AUFO::Move(const float _deltaTime)
{
	const Vector2f& _newLoc = GetLocation() + direction * speed * _deltaTime;
	SetLocation(_newLoc);
}

void AUFO::ComputeDirection()
{
	direction =
	{
		GetRandomNumberInRange(-1.0f, 1.0f),
		GetRandomNumberInRange(-1.0f, 1.0f)
	};
}

void AUFO::OnDeath()
{
	Super::OnDeath();
}

void AUFO::CollisionEnter(const CollisionData& _data)
{
	Super::CollisionEnter(_data);

	if (_data.channelName == "Projectile")
	{
		if (AProjectile* _projectile = Cast<AProjectile>(_data.other))
		{
			if (!_projectile->GetIsPlayerProjectile()) return;

			_projectile->GetLife()->RemoveLife();
		}
	}
	else if (_data.channelName == "Player")
	{
		if (APlayerPawn* _player = Cast<APlayerPawn>(_data.other))
		{
			_player->GetLife()->RemoveLife();
		}
	}

	//LOG(Warning, "CollisionEnter");
}

void AUFO::UpdateShootTime(const float _deltaTime)
{
	currentShootTime += _deltaTime;

	if (currentShootTime >= shootTimer)
	{
		currentShootTime = 0.0f;
		shootComponent->Shoot();
	}
}

void AUFO::UpdateDirectionTime(const float _deltaTime)
{
	currentDirectionTime += _deltaTime;

	if (currentDirectionTime >= directionTimer)
	{
		currentDirectionTime = 0.0f;
		ComputeDirection();
	}
}
