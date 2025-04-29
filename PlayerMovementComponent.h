#pragma once

#include "Component.h"

class UPlayerMovementComponent : public UComponent
{
	float deltaTime = 0.0f;
	float moveSpeed = 200.0f;
	float rotateSpeed = 30.0f;

	float currentAngle = 270.0f;
	float friction = 0.9f;

	Vector2f maxVelocity = Vector2f(0.5f, 0.5f);
	Vector2f acceleration = Vector2f();
	Vector2f velocity;
	Vector2f direction = Vector2f(1.0f, 1.0f);

public:
	FORCEINLINE virtual UComponent* Clone(AActor* _owner) const override
	{
		return new UPlayerMovementComponent(_owner, *this);
	}
public:
	UPlayerMovementComponent(AActor* _owner);
	UPlayerMovementComponent(AActor* _owner, const UPlayerMovementComponent& _other);

private:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;

public:
	void Move(const float _deltaTime);
	void MoveLeft();
	void MoveRight();
	void Rotate(const float _degree);
	void UpdateDirection();
	void ComputeAcceleration();
};

