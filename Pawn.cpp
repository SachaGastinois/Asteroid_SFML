#include "Pawn.h"
#include "InputManager.h"
#include "Level.h"

APawn::APawn(Level* _level, const string& _name) : AActor(_level, _name)
{
	controller = _level->GetGameMode()->GetPlayerController();
}

APawn::APawn(const APawn& _other) : AActor(_other)
{
	controller = _other.controller;
}


void APawn::Construct()
{
	Super::Construct();

	Input::InputManager& _inputManager = controller->GetInputManager();
	SetupInputController(_inputManager);
}