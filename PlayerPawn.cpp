#include "PlayerPawn.h"
#include "StaticMeshComponent.h"
#include "PlayerMovementComponent.h"
#include "CollisionComponent.h"
#include "AnimationComponent.h"
#include "CameraComponent.h"
#include "ShootComponent.h"
#include "LifeComponent.h"
#include "Asteroid.h"
#include "UFO.h"
#include "Bounds.h"
#include "Level.h"
#include "Projectile.h"
#include "ClassicModeLevel.h"
#include "ChronoModeLevel.h"

using namespace Input;
using namespace Camera;

APlayerPawn::APlayerPawn(Level* _level, const string& _name) : APawn(_level, _name)
{
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(RectangleShapeData(
			Vector2f(50.0f, 50.0f), "Player/SpaceShipSpriteSheet", PNG));
	hitBoxMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(RectangleShapeData(
			Vector2f(50.0f, 50.0f), "Utility/Transparent", PNG));
	animationComponent = CreateDefaultSubobject<UAnimationComponent>();
	collisionComponent = CreateDefaultSubobject<UCollisionComponent>(hitBoxMeshComponent, "Player", IS_ALL, CT_BLOCK);
	movementComponent = CreateDefaultSubobject<UPlayerMovementComponent>();
	shootComponent = CreateDefaultSubobject<UShootComponent>();
	lifeComponent = CreateDefaultSubobject<ULifeComponent>(FLifeData(5, 3, [&]() { OnDeath(); }));

	meshComponent->SetupAttachment(root);
	hitBoxMeshComponent->SetupAttachment(root);
	animationComponent->SetupAttachment(root);
}

APlayerPawn::APlayerPawn(const APlayerPawn& _other) : APawn(_other)
{

}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	Init();
}

void APlayerPawn::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void APlayerPawn::SetupInputController(Input::InputManager& _inputManager)
{
	ActionMap* _action = _inputManager.CreateActionMap("Movement");

	////////////////////////////////////////////////////////////
	///
	/// Forward Inputs
	///
	////////////////////////////////////////////////////////////

	_action->AddAction(new Action("ForwardHold", ActionData(ActionType::KeyHold, Z), 
		[&]() { 
			movementComponent->ComputeAcceleration();
		}));
	_action->AddAction(new Action("ForwardPressed", ActionData(ActionType::KeyPressed, Z),
		[&]() {
			movementComponent->GetSample()->Play();
			animationComponent->SwitchCurrentAnimation(animations["Forward"]);
		}));
	_action->AddAction(new Action("ForwardReleased", ActionData(ActionType::KeyReleased, Z), 
		[&]() { 
			movementComponent->GetSample()->Stop();
			animationComponent->SwitchCurrentAnimation(animations["Idle"]);
		}));



	////////////////////////////////////////////////////////////
	///
	/// Left / Right Inputs
	///
	////////////////////////////////////////////////////////////

	_action->AddAction(new Action("Left", ActionData(ActionType::KeyHold, Q),
		[&]() { 
			movementComponent->Rotate(-10.0f);
		}));
	_action->AddAction(new Action("Right", ActionData(ActionType::KeyHold, D),
		[&]() { 
			movementComponent->Rotate(10.0f);
		}));
	

	////////////////////////////////////////////////////////////
	///
	/// Shoot
	///
	////////////////////////////////////////////////////////////

	_action->AddAction(new Action("SpaceBarShoot", ActionData(ActionType::KeyPressed, Space),
		[&]() { 
			if (!canShoot) return;
			shootComponent->Shoot();
		}));
	_action->AddAction(new Action("SKeyShoot", ActionData(ActionType::KeyPressed, S),
		[&]() { 
			if (!canShoot) return;
			shootComponent->Shoot();
		}));


	////////////////////////////////////////////////////////////
	///
	/// Pause
	///
	////////////////////////////////////////////////////////////

	_action->AddAction(new Action("Pause", ActionData(ActionType::KeyPressed, Escape),
		[&]() { 
			if (UGameplayLevel* _level = Cast<UGameplayLevel>(GetLevel()))
			{
				if (_level->GetIsPause()) return;

				_level->GetGameMode()->GetHUD()->AddToViewport(_level->GetPauseCanvas());
				_level->GetPauseCanvas()->SetVisibility(VisibilityType::Visible);
				_level->SetIsPause(true);
			}
		}));

	_action->Enable();
}

void APlayerPawn::Init()
{
	SetZOrder(2);
	GetLevel()->GetCameraManager().SetZOrder(meshComponent->GetRenderMeshToken(), zOrder);


	spriteSize = Vector2i(56, 45);

	meshComponent->SetOriginAtMiddle();

	SetupSockets();

	UpdateShootStage();

	SetupAnimations();

	SetupCollisions();

}

void APlayerPawn::SetupSockets()
{
	vector<FSocketData> _sockets;

	const vector<Vector2f>& _relativeLocs =
	{
		{ 20.0f, 0.0f },  // canon haut
		{ 10.0f, -15.0f }, // canon gauche
		{ 10.0f, 15.0f }  // canon droit
	};

	const int _size = static_cast<int>(_relativeLocs.size());
	for (int _index = 0; _index < _size; _index++)
	{
		AActor* _socket = GetLevel()->SpawnActor<AActor>("Socket");
		_sockets.push_back(FSocketData(_socket, _relativeLocs[_index]));
	}

	shootComponent->SetSockets(_sockets);
}


void APlayerPawn::UpdateShootStage()
{
	vector<FSocketData>& _sockets = shootComponent->GetSockets();
	const int upgradeStage = shootComponent->GetUpgradeStage();
	if (upgradeStage == 0)
	{
		_sockets[0].isActive = true;
		_sockets[1].isActive = false;
		_sockets[2].isActive = false;
	}
	else if (upgradeStage == 1)
	{
		_sockets[0].isActive = false;
		_sockets[1].isActive = true;
		_sockets[2].isActive = true;
	}
	else if (upgradeStage == 2)
	{
		_sockets[0].isActive = true;
		_sockets[1].isActive = true;
		_sockets[2].isActive = true;
	}
}

void APlayerPawn::SetupAnimations()
{
	////////////////////////////////////////////////////////////
	///
	/// Idle Animation
	///
	////////////////////////////////////////////////////////////

	const vector<SpriteData>& _idleAnimationSpritesData =
	{
		SpriteData(Vector2i(0, 0), spriteSize),
	};
	Animation* _idleAnim = animationComponent->AddAnimation(_idleAnimationSpritesData, 0.0f, "Idle", meshComponent->GetShape());
	animations.insert(pair<string, Animation*>("Idle", _idleAnim));
	animationComponent->SetCurrentAnimation(animations["Idle"]);



	////////////////////////////////////////////////////////////
	///
	/// Forward Animation
	///
	////////////////////////////////////////////////////////////

	const vector<SpriteData>& _forwardAnimationSpritesData =
	{
		SpriteData(Vector2i(0, 45), spriteSize),
		SpriteData(Vector2i(0, 90), spriteSize),
		SpriteData(Vector2i(0, 135), spriteSize),
	};
	Animation* _forwardAnim = animationComponent->AddAnimation(_forwardAnimationSpritesData, 0.2f, "Forward", meshComponent->GetShape());
	animations.insert(pair<string, Animation*>("Forward", _forwardAnim));



	////////////////////////////////////////////////////////////
	///
	/// Shoot Animation
	///
	////////////////////////////////////////////////////////////

	// TODO Shoot Animation



	animationComponent->StartAnimation();
}

void APlayerPawn::SetupCollisions()
{
	collisionComponent->SetInformation("Player", IS_ALL, CT_BLOCK);
	collisionComponent->AddResponses({ {"Player", CT_NONE} });
	collisionComponent->AddResponses({ {"UFO", CT_BLOCK} });
	collisionComponent->AddResponses({ {"Asteroid", CT_BLOCK} });
	collisionComponent->AddResponses({ {"Projectile", CT_BLOCK} });

	collisionComponent->GetBounds()->SetBoundsData(new RectangleBoundsData(GetLocation(), {50.0f,50.0f}, degrees(0.0f)));
}

void APlayerPawn::OnDeath()
{
	LOG(Warning, "Joueur est Mort");

	if (UGameplayLevel* _level = Cast<UGameplayLevel>(GetLevel()))
	{
		SetActive(false);

		SetCanShoot(false);

		lifeComponent->SetCanBeAttacked(false);

		_level->SetIsPause(true);

		_level->GetGameMode()->GetHUD()->RemoveFromViewport(_level->GetPauseCanvas());
		_level->GetPauseCanvas()->SetVisibility(VisibilityType::Hidden);

		_level->GetGameMode()->GetHUD()->AddToViewport(_level->GetGameOverCanvas());
		_level->GetGameOverCanvas()->SetVisibility(VisibilityType::Visible);
	}
	if (UChronoModeLevel* _level = Cast<UChronoModeLevel>(GetLevel()))
	{
		_level->SetTimerRunning(false);
	}
}

void APlayerPawn::CollisionEnter(const CollisionData& _data)
{
	Super::CollisionEnter(_data);

	if (_data.channelName == "Projectile")
	{
		if (AProjectile* _projectile = Cast<AProjectile>(_data.other))
		{
			if (_projectile->GetIsPlayerProjectile()) return;

			_projectile->GetLife()->RemoveLife();
		}
	}
	else if (_data.channelName == "Asteroid")
	{
		if (AAsteroid* _asteroid = Cast<AAsteroid>(_data.other))
		{
			_asteroid->GetLife()->RemoveLife();
			if (UGameplayLevel* _level = Cast<UGameplayLevel>(GetLevel()))
			{
				_level->AddPoints(_asteroid->GetPoint());
			}
		}
	}
	else if (_data.channelName == "UFO")
	{
		if (AUFO* _ufo = Cast<AUFO>(_data.other))
		{
			_ufo->GetLife()->RemoveLife();
			if (UGameplayLevel* _level = Cast<UGameplayLevel>(GetLevel()))
			{
				_level->AddPoints(_ufo->GetPoint());
			}
		}
	}


	//LOG(Warning, "CollisionEnter");
}

void APlayerPawn::CollisionExit(const CollisionData& _data)
{
	Super::CollisionExit(_data);

	//LOG(Error, "CollisionExit");
}

void APlayerPawn::CollisionUpdate(const CollisionData& _data)
{
	Super::CollisionUpdate(_data);

	//LOG(Display, "CollisionUpdate");
}
