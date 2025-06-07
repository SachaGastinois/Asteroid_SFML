#include "ShootComponent.h"
#include "PlayerPawn.h"
#include "PlayerMovementComponent.h"
#include "Projectile.h"
#include "Level.h"
#include "UFO.h"

UShootComponent::UShootComponent(AActor* _owner) : UComponent(_owner)
{
	upgradeStage = 0;
}

UShootComponent::UShootComponent(AActor* _owner, const vector<FSocketData>& _sockets) : UComponent(_owner)
{
	upgradeStage = 0;
	sockets = _sockets;
}

UShootComponent::UShootComponent(AActor* _owner, const UShootComponent& _other) : UComponent(_owner, _other)
{
	upgradeStage = 0;
	sockets = _other.sockets;
}

void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	sample = owner->GetLevel()->SpawnSample<SoundSample>("ShootEffect");
	sample->SetVolume(5.0f);
}

void UShootComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	UpdateSocket();
}

void UShootComponent::UpdateSocket()
{
	float  _offset = 10.0f;

	if (APlayerPawn* _player = Cast<APlayerPawn>(owner))
	{
		for (FSocketData _socketData : sockets)
		{
			const Vector2f& _relativeLoc = _socketData.relativeLoc;
			const Vector2f& _direction = _player->GetMovement()->GetDirection();

			Vector2f _newLoc;
			_newLoc.x = owner->GetLocation().x - _offset + (_relativeLoc.x * _direction.x - _relativeLoc.y * _direction.y);
			_newLoc.y = owner->GetLocation().y - _offset + (_relativeLoc.x * _direction.y + _relativeLoc.y * _direction.x);

			_socketData.socket->SetLocation(_newLoc);
		}
	}
	else if (AUFO* _ufo = Cast<AUFO>(owner))
	{
		for (FSocketData _socketData : sockets)
		{
			const Vector2f& _relativeLoc = _socketData.relativeLoc;
			const Vector2f& _direction = _ufo->GetDirection();

			Vector2f _newLoc;
			_newLoc.x = owner->GetLocation().x + (_relativeLoc.x * _direction.x - _relativeLoc.y * _direction.y);
			_newLoc.y = owner->GetLocation().y + (_relativeLoc.x * _direction.y + _relativeLoc.y * _direction.x);

			_socketData.socket->SetLocation(_newLoc);
		}
	}
}

void UShootComponent::Shoot()
{
	for (FSocketData _socket : sockets)
	{
		if (!_socket.isActive) continue;

		AProjectile* _projectile = nullptr;
		if (Cast<APlayerPawn>(owner))
		{
 			_projectile = owner->GetLevel()->SpawnActor<AProjectile>("Player/BlueProjectileSpriteSheet", true);
			_projectile->SetRotation(owner->GetRotation());
		}
		else if (AUFO* _ufo = Cast<AUFO>(owner))
		{
			_projectile = owner->GetLevel()->SpawnActor<AProjectile>("Player/RedProjectileSpriteSheet", false);
			_projectile->SetRotation(degrees(GetRandomNumberInRange(0.0f, 360.0f)));
		}

		if (!_projectile) return;
		
		_projectile->SetLocation(_socket.socket->GetLocation());
		sample->SetLoop(false);
		sample->Play();
	}
}

void UShootComponent::SetUpgradeStage(const int _upgradeStage)
{
	if (APlayerPawn* _player = Cast<APlayerPawn>(owner))
	{
		upgradeStage = _upgradeStage;
		_player->UpdateShootStage();
	}
}
