#pragma once

#include "Pawn.h"

class UStaticMeshComponent;
class UPlayerMovementComponent;
class UAnimationComponent;
class UCollisionComponent;
class SpriteData;
class ShapeObject;
class Animation;

class APlayerPawn : public APawn
{
	UStaticMeshComponent* meshComponent;
	UStaticMeshComponent* hitBoxMeshComponent;
	UCollisionComponent* collisionComponent;
	UPlayerMovementComponent* movementComponent;
	UAnimationComponent* animationComponent;

	map<string, Animation*> animations;
	Vector2i spriteSize;
public:
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return meshComponent; }
	FORCEINLINE UPlayerMovementComponent* GetMovement() const { return movementComponent; }
	FORCEINLINE UAnimationComponent* GetAnimation() const { return animationComponent; }
public:
	APlayerPawn(Level* _level, const string& _name = "APawn");
	APlayerPawn(const APlayerPawn& _other);

protected:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void SetupInputController(Input::InputManager& _inputManager) override;

	void Init();
	void SetupAnimations();
	void SetupCollisions();

	virtual void CollisionEnter(const CollisionData& _data) override;
	virtual void CollisionExit(const CollisionData& _data) override;
	virtual void CollisionUpdate(const CollisionData& _data) override;
};
