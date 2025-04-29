#pragma once

#include "Component.h"

class UMovementComponent : public UComponent
{
	float moveSpeed = 200.0f;
	float speedFactor = 100.0f;
	float deltaTime = 0.0f;


public:
	FORCEINLINE virtual UComponent* Clone(AActor* _owner) const override
	{
		return new UMovementComponent(_owner, *this);
	}
public:
	UMovementComponent(AActor* _owner);
	UMovementComponent(AActor* _owner, const UMovementComponent& _other);

private:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;

public:
	void MoveForward();
	void MoveBackward();
	void MoveLeft();
	void MoveRight();
};
