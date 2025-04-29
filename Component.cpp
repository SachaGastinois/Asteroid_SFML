#include "Component.h"
#include "Actor.h"

UComponent::UComponent(AActor* _owner)
{
	owner = _owner;
	attachmentComponent = nullptr;
}

UComponent::UComponent(AActor* _owner, const UComponent& _other)
{
	owner = _owner;
	attachmentComponent = nullptr;
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

void UComponent::SetupAttachment(UComponent* _component)
{
	attachmentComponent = _component;
}
