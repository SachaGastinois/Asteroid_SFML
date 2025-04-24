#include "CameraActor.h"

Camera::ACameraActor::ACameraActor(Level* _level, const string& _name) : AActor(_level, _name)
{
	camera = CreateDefaultSubobject<UCameraComponent>();
}

Camera::ACameraActor::ACameraActor(Level* _level, const Vector2f& _center, const Vector2f& _size, const string& _name) : AActor(_level, _name)
{
	camera = CreateDefaultSubobject<UCameraComponent>(_center, _size);
}

Camera::ACameraActor::ACameraActor(Level* _level, const Vector2f& _size, const string& _name) : AActor(_level, _name)
{
	camera = CreateDefaultSubobject<UCameraComponent>(_size);
}

Camera::ACameraActor::ACameraActor(Level* _level, const FloatRect& _rect, const string& _name) : AActor(_level, _name)
{
	camera = CreateDefaultSubobject<UCameraComponent>(_rect);
}

Camera::ACameraActor::ACameraActor(const ACameraActor& _other) : AActor(_other)
{
	camera = CreateDefaultSubobject<UCameraComponent>(*_other.camera);
}