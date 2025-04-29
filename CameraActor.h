#pragma once
#include "Actor.h"
#include "CameraComponent.h"

namespace Camera
{
	class ACameraActor : public AActor
	{
		UCameraComponent* camera;

	public:
		FORCEINLINE UCameraComponent* GetCamera() const
		{
			return camera;
		}
		FORCEINLINE void SetViewport(const FloatRect& _rect)
		{
			camera->SetViewport(_rect);
		}
		FORCEINLINE virtual void SetLocation(const Vector2f& _center) override
		{
			Super::SetLocation(_center);
			camera->SetCenter(_center);
		}
		FORCEINLINE virtual void SetRotation(const Angle& _angle) override
		{
			Super::SetRotation(_angle);
			camera->SetRotation(_angle);
		}
		FORCEINLINE virtual void SetScale(const Vector2f& _scale) override
		{
			Super::SetScale(_scale);
			camera->SetSize(_scale);
		}
		FORCEINLINE void SetScissor(const FloatRect& _rect)
		{
			camera->SetScissor(_rect);
		}
		FORCEINLINE virtual void Move(const Vector2f& _offset) override
		{
			Super::Move(_offset);
			camera->Move(_offset);
		}
		FORCEINLINE virtual void Rotate(const Angle& _angle) override
		{
			Super::Rotate(_angle);
			camera->Rotate(_angle);
		}
		FORCEINLINE void Zoom(const float _factor)
		{
			camera->Zoom(_factor);
		}

	public:
		ACameraActor(Level* _level, const string& _name = "CameraActor");
		ACameraActor(Level* _level, const Vector2f& _center, const Vector2f& _size, const string& _name);
		ACameraActor(Level* _level, const Vector2f& _size, const string& _name);
		ACameraActor(Level* _level, const FloatRect& _rect, const string& _name);
		ACameraActor(const ACameraActor& _other);
	};
}