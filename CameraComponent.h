#pragma once
#include "Component.h"

namespace Camera
{
	class UCameraComponent : public UComponent
	{
		View* view;

	public:
		FORCEINLINE View* GetView() const
		{
			return view;
		}
		FORCEINLINE FloatRect GetViewport() const
		{
			return view->getViewport();
		}
		FORCEINLINE void SetViewport(const FloatRect& _rect)
		{
			view->setViewport(_rect);
		}
		FORCEINLINE void SetCenter(const Vector2f& _center)
		{
			view->setCenter(_center);
		}
		FORCEINLINE void SetRotation(const Angle& _angle)
		{
			view->setRotation(_angle);
		}
		FORCEINLINE void SetSize(const Vector2f& _size)
		{
			view->setSize(_size);
		}
		FORCEINLINE void SetScissor(const FloatRect& _rect)
		{
			view->setScissor(_rect);
		}
		FORCEINLINE void Move(const Vector2f& _offset)
		{
			view->move(_offset);
		}
		FORCEINLINE void Rotate(const Angle& _angle)
		{
			view->rotate(_angle);
		}
		FORCEINLINE void Zoom(const float _factor)
		{
			view->zoom(_factor);
		}
		FORCEINLINE virtual UComponent* Clone(AActor* _owner) const override
		{
			return new UCameraComponent(_owner, *this);
		}

	public:
		UCameraComponent(AActor* _owner);
		UCameraComponent(AActor* _owner, const Vector2f& _center, const Vector2f& _size);
		UCameraComponent(AActor* _owner, const Vector2f& _size);
		UCameraComponent(AActor* _owner, const FloatRect& _rect);
		UCameraComponent(AActor* _owner, const UCameraComponent& _other);
		~UCameraComponent();
	};
}