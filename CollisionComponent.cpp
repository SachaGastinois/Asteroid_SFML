#include "CollisionComponent.h"
#include "CollisionManager.h"
#include "ActorManager.h"
#include "MeshActor.h"
#include "Level.h"

UCollisionComponent::UCollisionComponent(AActor* _owner, const string& _channelName, const int _status, const CollisionType& _type) : UComponent(_owner)
{
	channelName = _channelName;
	type = _type;
	status = _status;
	bounds = new Bounds();
}

UCollisionComponent::UCollisionComponent(AActor* _owner, const UCollisionComponent& _other) : UComponent(_owner)
{
	channelName = _other.channelName;
	type = _other.type;
	status = _other.status;
	responses = _other.responses;
	*bounds = *_other.bounds;
}

UCollisionComponent::~UCollisionComponent()
{
	delete bounds->GetData();
	delete bounds;
}


void UCollisionComponent::Construct()
{
	Super::Construct();

	if (channelName != "NONE")
	{
		GetOwner()->GetLevel()->GetCollisionManager().AddCollision(this);
	}
}

void UCollisionComponent::Deconstruct()
{
	Super::Deconstruct();

	GetOwner()->GetLevel()->GetCollisionManager().RemoveCollision(this);
}

void UCollisionComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (channelName != "NONE")
	{
		ComputeCollisions();
	}
}


void UCollisionComponent::ComputeCollisions()
{
	if (!(status & IS_PHYSIC)) return;

	CollisionManager* _collisionManager = &owner->GetLevel()->GetCollisionManager();
	const set<UCollisionComponent*>& _allComponent = _collisionManager->GetAllCollisionComponents();

	for (UCollisionComponent* _otherComponent : _allComponent)
	{
		UpdateBounds();
		_otherComponent->UpdateBounds();
		if (_otherComponent == this) continue;
		if (_collisionManager->ContainsPair(owner, _otherComponent->owner)) continue;

		const string& _otherName = _otherComponent->GetChannelName();
		if (!responses.contains(_otherName)) continue;

		const CollisionType& _otherResponse = responses.at(_otherName);
		CollisionType _ownerResponse;
		if (_otherComponent->responses.contains(channelName))
		{
			_ownerResponse = _otherComponent->responses.at(channelName);
		}
		else
		{
			_ownerResponse = type;
		}
		if (_otherResponse == CT_NONE) continue;

		AActor* _other = _otherComponent->owner;

		if (Bounds* _intersection = bounds->FindIntersections(_otherComponent->bounds))
		{
			const CollisionStep& _step = ComputeStep(_other, CS_ENTER);
			const CollisionData& _ownerData = { owner, _ownerResponse, *_intersection, _step, channelName };
			const CollisionData& _otherData = { _other, _otherResponse, *_intersection, _step, _otherComponent->channelName };
			_collisionManager->Collide(_ownerData, _otherData);
		}

		else if (othersStep.contains(_otherComponent->owner))
		{
			othersStep.erase(_other);
			const CollisionStep& _step = ComputeStep(_other, CS_EXIT);
			const CollisionData& _ownerData = { owner, _ownerResponse, Bounds(), _step, channelName };
			const CollisionData& _otherData = { _other, _otherResponse, Bounds(), _step, _otherComponent->channelName };
			_collisionManager->Collide(_ownerData, _otherData);
		}
	}
}

CollisionStep UCollisionComponent::ComputeStep(AActor* _other, const CollisionStep& _step)
{
	if (othersStep.contains(_other) && othersStep[_other] == CS_ENTER ||_step != CS_EXIT && othersStep[_other] == CS_UPDATE)
	{
		othersStep[_other] = CS_UPDATE;
	}
	else
	{
		othersStep[_other] = _step;
	}
	return othersStep[_other];

}

void UCollisionComponent::UpdateBounds()
{
	bounds->UpdateBounds(owner);
}