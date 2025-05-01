#include "PlayerPawn.h"
#include "StaticMeshComponent.h"
#include "PlayerMovementComponent.h"
#include "CameraComponent.h"
#include "Level.h"

using namespace Input;
using namespace Camera;

APlayerPawn::APlayerPawn(Level* _level, const string& _name) : APawn(_level, _name)
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(RectangleShapeData(Vector2f(50.0f, 50.0f)));
	movement = CreateDefaultSubobject<UPlayerMovementComponent>();

	mesh->SetupAttachment(root);
}

APlayerPawn::APlayerPawn(const APlayerPawn& _other) : APawn(_other)
{

}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	mesh->SetOriginAtMiddle();
}

void APlayerPawn::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
	ComputeNewLocation();
}

void APlayerPawn::SetupInputController(Input::InputManager& _inputManager)
{
	ActionMap* _action = _inputManager.CreateActionMap("Movement");

	_action->AddAction(new Action("Forward", ActionData(ActionType::KeyHold, Z), 
		[&]() { movement->ComputeAcceleration(); }));
	_action->AddAction(new Action("Left", ActionData(ActionType::KeyHold, Q),
		[&]() { movement->MoveLeft(); }));
	_action->AddAction(new Action("Right", ActionData(ActionType::KeyHold, D),
		[&]() { movement->MoveRight(); }));

	_action->Enable();
}

void APlayerPawn::ComputeNewLocation()
{
	const Vector2f& _windowSize = CAST(Vector2f, GetLevel()->GetWindowSize());
	const Vector2f& _playerPosition = GetLocation();
	const Vector2f& _playerScale = GetScale();
	const Vector2f& _playerSize = Vector2f(_playerScale.x, _playerScale.y) / 2.0f;
	if ((_playerPosition.x + _playerSize.x) < 0.0f)
	{
		SetLocation({ _windowSize.x + _playerSize.x, _playerPosition.y });
	}
	else if ((_playerPosition.x - _playerSize.x) > _windowSize.x)
	{
		SetLocation({ 0.0f - _playerSize.x, _playerPosition.y });
	}
	if ((_playerPosition.y + _playerSize.y) < 0.0f)
	{
		SetLocation({ _playerPosition.x , _windowSize.y + _playerSize.y });
	}
	else if ((_playerPosition.y - _playerSize.y) > _windowSize.y)
	{
		SetLocation({ _playerPosition.x, 0.0f - _playerSize.y });
	}
}
