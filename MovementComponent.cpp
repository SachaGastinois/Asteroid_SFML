#include "MovementComponent.h"
#include "Actor.h"

UMovementComponent::UMovementComponent(AActor* _owner) : UComponent(_owner)
{
}

UMovementComponent::UMovementComponent(AActor* _owner, const UMovementComponent& _other) : UComponent(_owner)
{
}

void UMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UMovementComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	const Vector2f& _newLoc = owner->GetPosition() + Vector2f(1.0f, -1.0f) * moveSpeed * _deltaTime;
}
