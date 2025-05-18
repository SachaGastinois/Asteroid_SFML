#pragma once
#include "Singleton.h"
#include "CollisionComponent.h"

class CollisionManager
{
	set<UCollisionComponent*> allCollisionComponents;
	set<pair<AActor*, AActor*>> hasCollision;

public:
	FORCEINLINE void AddCollision(UCollisionComponent* _component)
	{
		allCollisionComponents.insert(_component);
	}
	FORCEINLINE void RemoveCollision(UCollisionComponent* _component)
	{
		allCollisionComponents.erase(_component);
	}
	FORCEINLINE void AddCollisionPair(AActor* _owner, AActor* _other)
	{
		if (ContainsPair(_owner, _other)) return;
		hasCollision.insert({ _owner , _other });
	}
	FORCEINLINE void RemoveCollisionpair(AActor* _owner, AActor* _other)
	{
		if (!ContainsPair(_owner, _other)) return;
		hasCollision.erase({ _owner, _other });
	}
	FORCEINLINE void ResetCollisionPair()
	{
		hasCollision.clear();
	}
	FORCEINLINE bool ContainsPair(AActor* _owner, AActor* _other)
	{
		if (/*hasCollision.contains({ _owner, _other }) ||*/ hasCollision.contains({ _other ,_owner }))
		{
			return true;
		}
		return false;
	}
	FORCEINLINE set<UCollisionComponent*> GetAllCollisionComponents() const
	{
		return allCollisionComponents;
	}

public:
	void Collide(const CollisionData& _owner, const CollisionData& _other);
};