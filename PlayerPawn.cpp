#include "PlayerPawn.h"
#include "StaticMeshComponent.h"
#include "PlayerMovementComponent.h"
#include "CollisionComponent.h"
#include "AnimationComponent.h"
#include "CameraComponent.h"
#include "Bounds.h"
#include "Level.h"

using namespace Input;
using namespace Camera;

APlayerPawn::APlayerPawn(Level* _level, const string& _name) : APawn(_level, _name)
{
	spriteSize = Vector2i(45, 56);

	movementComponent = CreateDefaultSubobject<UPlayerMovementComponent>();
	meshComponent = CreateDefaultSubobject<UStaticMeshComponent>(RectangleShapeData(
			Vector2f(50.0f, 50.0f), "Player/SpaceShipSpriteSheet", PNG));
	hitBoxMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(RectangleShapeData(
			Vector2f(50.0f, 50.0f)));
	animationComponent = CreateDefaultSubobject<UAnimationComponent>();
	collisionComponent = CreateDefaultSubobject<UCollisionComponent>(hitBoxMeshComponent, "Player", IS_ALL, CT_BLOCK);

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
			animationComponent->SwitchCurrentAnimation(animations["Forward"]);
		}));
	_action->AddAction(new Action("ForwardReleased", ActionData(ActionType::KeyReleased, Z), 
		[&]() { 
			animationComponent->SwitchCurrentAnimation(animations["Idle"]);
		}));



	////////////////////////////////////////////////////////////
	///
	/// Left / Right Inputs
	///
	////////////////////////////////////////////////////////////

	_action->AddAction(new Action("Left", ActionData(ActionType::KeyHold, Q),
		[&]() { 
			movementComponent->Rotate(-10.0f);;
		}));
	_action->AddAction(new Action("Right", ActionData(ActionType::KeyHold, D),
		[&]() { 
			movementComponent->Rotate(10.0f);;
		}));



	_action->Enable();
}

void APlayerPawn::Init()
{
	meshComponent->SetOriginAtMiddle();
	hitBoxMeshComponent->SetOriginAtMiddle();

	SetupAnimations();

	SetupCollisions();
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
		SpriteData(Vector2i(45, 0), spriteSize),
		SpriteData(Vector2i(90, 0), spriteSize),
		SpriteData(Vector2i(135, 0), spriteSize),
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
	const vector<pair<string, CollisionType>>& _responses
	{
		{"Player", CT_NONE},
		{"Asteroid", CT_OVERLAP},
		{"UFO", CT_BLOCK},
		{"Projectile", CT_OVERLAP},
	};
	collisionComponent->AddResponses(_responses);
}

void APlayerPawn::CollisionEnter(const CollisionData& _data)
{
	if (!movementComponent) return;

	LOG(Warning, "CollisionEnter");
	if (RectangleBoundsData* _data = Cast<RectangleBoundsData>(collisionComponent->GetBounds()->GetData()))
	{
		LOG(Error, _data->size);
		LOG(Error, _data->position);
		LOG(Error, to_string(_data->rotation.asDegrees()));
	}
	if (_data.response == CT_BLOCK)
	{
		movementComponent->SetCanMove(false);
	}
}

void APlayerPawn::CollisionExit(const CollisionData& _data)
{
	if (!movementComponent) return;

	LOG(Error, "CollisionExit");
	if (_data.response == CT_BLOCK)
	{
		movementComponent->SetCanMove(true);
	}
}
