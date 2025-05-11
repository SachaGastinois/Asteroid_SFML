#pragma once

#include "Component.h"

class UPlayerMovementComponent : public UComponent
{
	bool canMove;

	float deltaTime;
	float rotateSpeed;

	float currentAngle;
	float friction;

	Vector2f maxVelocity;
	Vector2f acceleration;
	Vector2f velocity;
	Vector2f direction;

public:
	FORCEINLINE void SetCanMove(const bool _canMove)
	{
		canMove = _canMove;
	}
	FORCEINLINE virtual UComponent* Clone(AActor* _owner) const override
	{
		return new UPlayerMovementComponent(_owner, *this);
	}
	FORCEINLINE void ApplyFriction()
	{
		velocity *= friction;
	}
	FORCEINLINE float GetCurrentAngle() const
	{
		return currentAngle;
	}
public:
	UPlayerMovementComponent(AActor* _owner);
	UPlayerMovementComponent(AActor* _owner, const UPlayerMovementComponent& _other);

private:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;

public:
	void Move(const float _deltaTime);
	void Rotate(const float _degree);
	void UpdateDirection();
	void ComputeAcceleration();
};

