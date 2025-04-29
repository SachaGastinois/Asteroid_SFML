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

	deltaTime = _deltaTime;
}

void UMovementComponent::MoveForward()
{
	const Vector2f& _newLoc = owner->GetLocation() + Vector2f(0.0f, -1.0f) * moveSpeed * speedFactor * deltaTime;
	owner->SetLocation(_newLoc);
}

void UMovementComponent::MoveBackward()
{
	const Vector2f& _newLoc = owner->GetLocation() + Vector2f(0.0f, 1.0f) * moveSpeed * speedFactor * deltaTime;
	owner->SetLocation(_newLoc);
}

void UMovementComponent::MoveLeft()
{
	const Vector2f& _newLoc = owner->GetLocation() + Vector2f(-1.0f, 0.0f) * moveSpeed * speedFactor * deltaTime;
	owner->SetLocation(_newLoc);
}

void UMovementComponent::MoveRight()
{
	const Vector2f& _newLoc = owner->GetLocation() + Vector2f(1.0f, 0.0f) * moveSpeed * speedFactor * deltaTime;
	owner->SetLocation(_newLoc);
}