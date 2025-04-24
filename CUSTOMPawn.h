#pragma once
#include "Pawn.h"
#include "StaticMeshComponent.h"
#include "CameraComponent.h"

class InputManager;

class CUSTOMPawn : public APawn
{
	UStaticMeshComponent* mesh;
	Camera::UCameraComponent* camera;

public:
	CUSTOMPawn(Level* _level, const string& _name = "CUSTOM Pawn");
	CUSTOMPawn(const CUSTOMPawn& _other);

protected:
	virtual void SetupInputController(Input::InputManager& _inputManager) override;
};