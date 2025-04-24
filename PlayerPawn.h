#pragma once

#include "Pawn.h"

class UStaticMeshComponent;
class UMovementComponent;

class APlayerPawn : public APawn
{
	UStaticMeshComponent* mesh;
	UMovementComponent* movement;
public:
	APlayerPawn(Level* _level, const string& _name = "APawn");
	APlayerPawn(const APlayerPawn& _other);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void SetupInputController(Input::InputManager& _inputManager) override;

};
