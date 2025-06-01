#pragma once

#include "Entity.h"

enum EAsteroidSize
{
	AS_SMALL = 1,
	AS_MEDIUM,
	AS_BIG,
	AS_COUNT,
};

class AAsteroid : public AEntity
{
	EAsteroidSize size;
	float speed;
	Vector2f direction;

public:
	AAsteroid(Level* _level, const EAsteroidSize& _size, const string& _name = "Actor", const TransformData& _transform = TransformData());
	AAsteroid(const AAsteroid& _other);

public:
	virtual void Construct() override;
	virtual void Deconstruct() override;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void BeginDestroy() override;

	void Init();
	void SetupAnimations();
	virtual void SetupCollisions() override;

	void Move(const float _deltaTime);

	virtual void OnDeath() override;

	virtual void CollisionEnter(const CollisionData& _data) override;

};

