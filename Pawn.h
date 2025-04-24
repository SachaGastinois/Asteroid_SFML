#pragma once
#include "Actor.h"
#include "PlayerController.h"

class InputManager;

class APawn : public AActor
{
protected:
	PlayerController* controller;

public:
	FORCEINLINE PlayerController* GetController() const
	{
		return controller;
	}
public:
	APawn(Level* _level, const string& _name = "Pawn");
	APawn(const APawn& _other);

protected:
	virtual void SetupInputController(Input::InputManager& _inputManager) {};

public:
	virtual void Construct() override;
};