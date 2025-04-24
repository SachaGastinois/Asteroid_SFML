#include "RootComponent.h"

URootComponent::URootComponent(AActor* _owner, const TransformData& _transform) : UComponent(_owner)
{
	transform = _transform;
}

URootComponent::URootComponent(AActor* _owner, const URootComponent& _other) : UComponent(_owner)
{
	transform = _other.transform;
}