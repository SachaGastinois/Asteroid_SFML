#include "Component.h"
#include "Actor.h"

UComponent::UComponent(AActor* _owner)
{
	owner = _owner;
}

UComponent::UComponent(AActor* _owner, const UComponent& _other)
{
	owner = _owner;
}


void UComponent::Construct()
{
	SetActive(true);
}

void UComponent::Deconstruct()
{
	SetActive(false);
}

void UComponent::BeginPlay()
{
	Construct();
}
