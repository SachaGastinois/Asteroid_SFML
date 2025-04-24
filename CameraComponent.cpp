#include "CameraComponent.h"
#include "Level.h"

Camera::UCameraComponent::UCameraComponent(AActor* _owner) : UComponent(_owner)
{
	const Vector2f& _windowSize = owner->GetLevel()->GetWindowSize();
	view = new View(_windowSize / 2.0f, _windowSize);
}

Camera::UCameraComponent::UCameraComponent(AActor* _owner, const Vector2f& _center, const Vector2f& _size) : UComponent(_owner)
{
	view = new View(_center, _size);
}

Camera::UCameraComponent::UCameraComponent(AActor* _owner, const Vector2f& _size) : UComponent(_owner)
{
	view = new View({ _size / 2.0f }, _size);
}

Camera::UCameraComponent::UCameraComponent(AActor* _owner, const FloatRect& _rect) : UComponent(_owner)
{
	view = new View(_rect);
}

Camera::UCameraComponent::UCameraComponent(AActor* _owner, const UCameraComponent& _other) : UComponent(_owner)
{
	view = new View(*_other.view);
}

Camera::UCameraComponent::~UCameraComponent()
{
	delete view;
}