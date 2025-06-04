#pragma once

#include "Component.h"

class SoundSample;

class UPlayerMovementComponent : public UComponent
{
	bool canMove;

	float deltaTime;

	float rotateSpeed;
	int degreesToRotate;
	bool canRotate;
	bool rotateLeft;
	float currentAngle;

	float friction;

	bool canAccelerate;
	Vector2f maxVelocity;
	Vector2f acceleration;
	Vector2f velocity;
	Vector2f direction;

	SoundSample* sample;

public:
	FORCEINLINE void SetCanMove(const bool _canMove)
	{
		canMove = _canMove;
	}
	FORCEINLINE void SetCanRotate(const bool _status)
	{
		canRotate = _status;
	}
	FORCEINLINE void SetCanAccelerate(const bool _status)
	{
		canAccelerate = _status;
	}
	FORCEINLINE void SetRotateLeft(const bool _status)
	{
		rotateLeft = _status;
	}
	FORCEINLINE SoundSample* GetSample()
	{
		return sample;
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
	/// <summary>
	/// Calcule la direction actuelle par rapport à l'angle actuel du transform
	/// </summary>
	/// <returns></returns>
	FORCEINLINE Vector2f GetDirection() const
	{
		Vector2f _direction = Vector2f();
		const float _rad = DegToRad(currentAngle);
		_direction.x = cos(_rad);
		_direction.y = sin(_rad);

		return _direction;
	}
public:
	UPlayerMovementComponent(AActor* _owner);
	UPlayerMovementComponent(AActor* _owner, const UPlayerMovementComponent& _other);

private:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;

public:
	void Move(const float _deltaTime);
	void Rotate();
	void UpdateDirection();
	void ComputeAcceleration();
};

