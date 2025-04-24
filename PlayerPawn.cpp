#include "PlayerPawn.h"
#include "StaticMeshComponent.h"
#include "MovementComponent.h"

APlayerPawn::APlayerPawn(Level* _level, const string& _name) : APawn(_level, _name)
{
	
}

APlayerPawn::APlayerPawn(const APlayerPawn& _other) : APawn(_other)
{

}

void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(RectangleShapeData(Vector2f(100.0f, 100.0f)));
	movement = CreateDefaultSubobject<UMovementComponent>();
}

void APlayerPawn::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);
}

void APlayerPawn::SetupInputController(Input::InputManager& _inputManager)
{

}
