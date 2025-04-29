#pragma once

#include "Pawn.h"

class UStaticMeshComponent;
class UPlayerMovementComponent;

class APlayerPawn : public APawn
{
	UStaticMeshComponent* mesh;
	UPlayerMovementComponent* movement;

public:
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return mesh; }
	FORCEINLINE UPlayerMovementComponent* GetMovement() const { return movement; }
public:
	APlayerPawn(Level* _level, const string& _name = "APawn");
	APlayerPawn(const APlayerPawn& _other);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void SetupInputController(Input::InputManager& _inputManager) override;

	void ComputeNewLocation();
};
