#pragma once
#include "PlayerController.h"

class CUSTOMPawn;

class CUSTOMPlayerController : public PlayerController
{
public:
	CUSTOMPlayerController(Level* _level, const string& _name = "CUSTOMPlayerController");
	CUSTOMPlayerController(const PlayerController& _other);

	virtual APawn* GetPawnRef() const override;
};