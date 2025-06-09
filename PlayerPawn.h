#pragma once

#include "Pawn.h"

class UStaticMeshComponent;
class UPlayerMovementComponent;
class UAnimationComponent;
class UCollisionComponent;
class UShootComponent;
class ULifeComponent;
class SpriteData;
class ShapeObject;
class Animation;

class APlayerPawn : public APawn
{
	UStaticMeshComponent* meshComponent;
	UStaticMeshComponent* hitBoxMeshComponent;
	//UStaticMeshComponent* explosionMeshComponent;
	UCollisionComponent* collisionComponent;
	UPlayerMovementComponent* movementComponent;
	UAnimationComponent* animationComponent;
	UShootComponent* shootComponent;
	ULifeComponent* lifeComponent;

	map<string, Animation*> animations;
	Vector2i spriteSize;

	bool canShoot;
public:
	FORCEINLINE void SetCanShoot(const bool _canShoot) { canShoot = _canShoot; }
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return meshComponent; }
	FORCEINLINE UStaticMeshComponent* GetHitBoxMesh() const { return hitBoxMeshComponent; }
	FORCEINLINE UCollisionComponent* GetCollision() const { return collisionComponent; }
	FORCEINLINE UPlayerMovementComponent* GetMovement() const { return movementComponent; }
	FORCEINLINE UAnimationComponent* GetAnimation() const { return animationComponent; }
	FORCEINLINE UShootComponent* GetShoot() const { return shootComponent; }
	FORCEINLINE ULifeComponent* GetLife() const { return lifeComponent; }

public:
	APlayerPawn(Level* _level, const string& _name = "APawn");
	APlayerPawn(const APlayerPawn& _other);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void SetupInputController(Input::InputManager& _inputManager) override;

	void Init();
	void SetupSockets();
	void SetupAnimations();
	void SetupCollisions();
	void OnDeath();

	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
public:
	void UpdateShootStage();
};
