#pragma once

#include "Entity.h"

class AProjectile : public AEntity
{
	float speed;
	bool isPlayerProjectile;
	
public:
	FORCEINLINE bool GetIsPlayerProjectile() const { return isPlayerProjectile; }

public:
	AProjectile(Level* _level, const string& _spriteSheetPath, const bool _isPlayerProjectile, const string& _name = "Projectile", const TransformData& _transform = TransformData());
	AProjectile(const AProjectile& _other);

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

