#pragma once

#include "Actor.h"
#include "LifeComponent.h"

class UStaticMeshComponent;
class UCollisionComponent;
class UAnimationComponent;
class Animation;

enum EHitBoxType
{
	HBT_CIRCLE,
	HBT_RECTANGLE,
	HBT_COUNT,
};

struct FEntityData
{
	Vector2f meshSize;
	Vector2f hitBoxSize;
	float hitBoxRadius;
	EHitBoxType hitBoxType;
	string meshPath;
	FLifeData lifeData;

	FEntityData() = default;
	FEntityData(const Vector2f& _meshSize, const Vector2f& _hitBoxSize, const string& _meshPath, 
		const FLifeData& _lifeData)
	{
		meshSize = _meshSize;
		hitBoxSize = _hitBoxSize;
		hitBoxType = HBT_RECTANGLE;
		meshPath = _meshPath;
		lifeData = _lifeData;
	}
	FEntityData(const Vector2f& _meshSize, const float _hitBoxRadius, const string& _meshPath,
		const FLifeData& _lifeData)
	{
		meshSize = _meshSize;
		hitBoxRadius = _hitBoxRadius;
		hitBoxType = HBT_CIRCLE;
		meshPath = _meshPath;
		lifeData = _lifeData;
	}
};

class AEntity : public AActor
{
protected:
	UStaticMeshComponent* meshComponent;
	UStaticMeshComponent* hitBoxMeshComponent;
	UCollisionComponent* collisionComponent;
	UAnimationComponent* animationComponent;
	ULifeComponent* lifeComponent;

	int point;

	map<string, Animation*> animations;
	Vector2i spriteSize;
public:
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return meshComponent; }
	FORCEINLINE UStaticMeshComponent* GetHitBoxMesh() const { return hitBoxMeshComponent; }
	FORCEINLINE UCollisionComponent* GetCollision() const { return collisionComponent; }
	FORCEINLINE UAnimationComponent* GetAnimation() const { return animationComponent; }
	FORCEINLINE ULifeComponent* GetLife() const { return lifeComponent; }
	FORCEINLINE int GetPoint() const { return point; }
public:
	AEntity(Level* _level, const int _point, const FEntityData& _data, const string& _name = "Actor", const TransformData& _transform = TransformData());
	AEntity(const AEntity& _other);

protected:
	virtual void Construct() override;
	virtual void Deconstruct() override;
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;
	virtual void BeginDestroy() override;

	void Init();
	virtual void SetupCollisions();
	virtual void OnDeath();
};

