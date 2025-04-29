#include "PlayerPawn.h"
#include "StaticMeshComponent.h"
#include "MovementComponent.h"
#include "CameraComponent.h"
#include "Level.h"

using namespace Input;
using namespace Camera;

APlayerPawn::APlayerPawn(Level* _level, const string& _name) : APawn(_level, _name)
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(RectangleShapeData(Vector2f(50.0f, 50.0f)));
	movement = CreateDefaultSubobject<UMovementComponent>();
	camera = CreateDefaultSubobject<Camera::UCameraComponent>();

	mesh->SetupAttachment(root);
	camera->SetupAttachment(root);
}

APlayerPawn::APlayerPawn(const APlayerPawn& _other) : APawn(_other)
{

}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();


}

void APlayerPawn::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void APlayerPawn::SetupInputController(Input::InputManager& _inputManager)
{
	ActionMap* _action = _inputManager.CreateActionMap("Movement");

	_action->AddAction(new Action("Forward", ActionData(ActionType::KeyHold, Z), 
		[&]() { movement->MoveForward(); }));
	_action->AddAction(new Action("Backward", ActionData(ActionType::KeyHold, S),
		[&]() { movement->MoveBackward(); }));
	_action->AddAction(new Action("Left", ActionData(ActionType::KeyHold, Q),
		[&]() { movement->MoveLeft(); }));
	_action->AddAction(new Action("Right", ActionData(ActionType::KeyHold, D),
		[&]() { movement->MoveRight(); }));

	_action->Enable();
}
