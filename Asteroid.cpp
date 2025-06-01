#include "Asteroid.h"
#include "StaticMeshComponent.h"
#include "PlayerMovementComponent.h"
#include "CollisionComponent.h"
#include "AnimationComponent.h"
#include "CameraComponent.h"
#include "CollisionComponent.h"
#include "Bounds.h"
#include "Level.h"
#include "Projectile.h"
#include "PlayerPawn.h"
#include "GameplayLevel.h"


AAsteroid::AAsteroid(Level* _level, const EAsteroidSize& _size, const string& _name, const TransformData& _transform)
	: AEntity(_level, 150 / _size, FEntityData(Vector2f(40.0f * _size, 40.0f * _size), 15.0f * _size, "Entity/Asteroid/AsteroidSpriteSheet_1",
	  FLifeData(1, 1, [&]() { OnDeath(); })), _name, _transform)
{
	size = _size;
	speed = 100.0f;
	direction = Vector2f();
}

AAsteroid::AAsteroid(const AAsteroid& _other) : AEntity(_other)
{
	size = _other.size;
	speed = _other.speed;
	direction = _other.direction;
}

void AAsteroid::Construct()
{
	Super::Construct();
}

void AAsteroid::Deconstruct()
{
	Super::Deconstruct();
}

void AAsteroid::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void AAsteroid::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	Move(_deltaTime);
}

void AAsteroid::BeginDestroy()
{
	Super::BeginDestroy();
}

void AAsteroid::Init()
{
	spriteSize = { 32, 32 };

	direction =
	{
		GetRandomNumberInRange(-1.0f, 1.0f),
		GetRandomNumberInRange(-1.0f, 1.0f)
	};

	SetZOrder(1);
	GetLevel()->GetCameraManager().SetZOrder(meshComponent->GetRenderMeshToken(), zOrder);

	SetupAnimations();
}

void AAsteroid::SetupAnimations()
{
	vector<SpriteData> _animationSpritesData;

	for (int _i = 0; _i < 26; _i++)
	{
		SpriteData _data = SpriteData({ spriteSize.x * _i, 0 }, spriteSize);
		_animationSpritesData.push_back(_data);
	}
	Animation* _anim = animationComponent->AddAnimation(_animationSpritesData, 2.0f, "Movement", meshComponent->GetShape());
	animations.insert(pair<string, Animation*>("Movement", _anim));
	animationComponent->SetCurrentAnimation(animations["Movement"]);
	animationComponent->StartAnimation();
}

void AAsteroid::SetupCollisions()
{
	Super::SetupCollisions();

	collisionComponent->SetInformation("Asteroid", IS_ALL, CT_BLOCK);
	collisionComponent->AddResponses({ {"Player", CT_BLOCK} });
	collisionComponent->AddResponses({ {"UFO", CT_NONE} });
	collisionComponent->AddResponses({ {"Asteroid", CT_NONE} });
	collisionComponent->AddResponses({ {"Projectile", CT_BLOCK} });
}

void AAsteroid::Move(const float _deltaTime)
{
	const Vector2f& _newLoc = GetLocation() + direction * speed * _deltaTime;
	SetLocation(_newLoc);
}

void AAsteroid::OnDeath()
{
	Super::OnDeath();

	if (size == EAsteroidSize::AS_SMALL) return;

	for (int _index = 0; _index < 2; _index++)
	{
		AAsteroid* _asteroid = GetLevel()->SpawnActor<AAsteroid>(EAsteroidSize(size - 1));
		_asteroid->GetLife()->SetCanBeAttacked(lifeComponent->GetCanBeAttacked());
		_asteroid->SetLocation(GetLocation());
	}
}

void AAsteroid::CollisionEnter(const CollisionData& _data)
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
