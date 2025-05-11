#pragma once
#include "Component.h"
#include "Bounds.h"

enum InteractStatus
{
	IS_NONE = 0,
	IS_QUERY = 1 << 0,
	IS_PHYSIC = 1 << 1,
	IS_ALL = IS_QUERY | IS_PHYSIC
};

enum CollisionType
{
	CT_NONE,
	CT_OVERLAP,
	CT_BLOCK
};

enum CollisionStep
{
	CS_ENTER,
	CS_UPDATE,
	CS_EXIT
};

struct CollisionData
{
	AActor* other;
	CollisionType response;
	Bounds impact;
	CollisionStep step;
	string channelName;
};

class UCollisionComponent : public UComponent
{
	int status;
	string channelName;
	CollisionType type;						 
	map<string, CollisionType> responses;	
	map<AActor*, CollisionStep> othersStep;
	Bounds* bounds;

public:
	FORCEINLINE void AddResponses(const vector<pair<string, CollisionType>>& _responses)
	{
		for (pair<string, CollisionType> _pair : _responses)
		{
			responses.insert(_pair);
		}
	}
	FORCEINLINE void SetInformation(const string& _channelName, const int _status, const CollisionType& _type)
	{
		channelName = _channelName;
		type = _type;
		status = _status;
	}
	FORCEINLINE string GetChannelName() const
	{
		return channelName;
	}

	FORCEINLINE Bounds* GetBounds() const
	{
		return bounds;
	}

	FORCEINLINE virtual UComponent* Clone(AActor* _owner) const override
	{
		return new UCollisionComponent(_owner, *this);
	}

public:
	UCollisionComponent(AActor* _owner, const string& _channelName = "NONE", const int _status = IS_NONE, const CollisionType& _type = CT_NONE);
	UCollisionComponent(AActor* _owner, UStaticMeshComponent* _meshComponent, const string& _channelName = "NONE", const int _status = IS_NONE, const CollisionType& _type = CT_NONE);
	UCollisionComponent(AActor* _owner, const UCollisionComponent& _other);
	~UCollisionComponent();

protected:
	virtual void Construct() override;
	virtual void Deconstruct() override;
	virtual void Tick(const float _deltaTime) override;

private:
	void ComputeCollisions();
	CollisionStep ComputeStep(AActor* _other, const CollisionStep& _step);
	void UpdateBounds();
};