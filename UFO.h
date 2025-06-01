#pragma once

#include "Entity.h"

class UShootComponent;
class SoundSample;

class AUFO : public AEntity
{
	float speed;
	Vector2f direction;

	float shootTimer;
	float currentShootTime;
	float directionTimer;
	float currentDirectionTime;

	UShootComponent* shootComponent;

public:
	FORCEINLINE Vector2f GetDirection() const { return direction; }

public:
	AUFO(Level* _level, const string& _meshPath, const string& _name = "Actor", const TransformData& _transform = TransformData());
	AUFO(const AUFO& _other);

public:
	virtual void Construct() override;
	virtual void Deconstruct() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void BeginDestroy() override;

	void Init();
	void SetupSocket();
	void SetupAnimations();
	virtual void SetupCollisions() override;

	void Move(const float _deltaTime);
	void ComputeDirection();

	virtual void OnDeath() override;

	virtual void CollisionEnter(const CollisionData& _data) override;

	void UpdateShootTime(const float _deltaTime);
	void UpdateDirectionTime(const float _deltaTime);
};

