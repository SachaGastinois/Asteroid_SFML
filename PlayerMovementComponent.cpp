#include "PlayerMovementComponent.h"
#include "Actor.h"
#include "PlayerPawn.h"
#include "TimerManager.h"
#include "StaticMeshComponent.h"
#include "AudioManager.h"
#include "SoundSample.h"
#include "Level.h"

UPlayerMovementComponent::UPlayerMovementComponent(AActor* _owner) : UComponent(_owner)
{
	canMove = true;

	rotateSpeed = 30.0f;
	degreesToRotate = 10.0f;
	canRotate = false;
	rotateLeft = false;
	currentAngle = 270.0f;

	canAccelerate = false;
	friction = 0.95f;
	accelerationFactor = 0.1f;
	maxVelocity = Vector2f(1.0f, 1.0f);
	acceleration = Vector2f();
	velocity = Vector2f();
	direction = Vector2f(0.0f, 0.0f);
}

UPlayerMovementComponent::UPlayerMovementComponent(AActor* _owner, 
	const UPlayerMovementComponent& _other) : UComponent(_owner, _other)
{
	canMove = _other.canMove;
	velocity = _other.velocity;
	friction = _other.friction;
	currentAngle = _other.currentAngle;
	maxVelocity = _other.maxVelocity;
	acceleration = _other.acceleration;
	direction = _other.direction;
}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	new Timer([&]()
	{
		ApplyFriction();
	}, seconds(0.25f), true, true);

	owner->SetRotation(Angle(degrees(currentAngle)));

	sample = owner->GetLevel()->SpawnSample<SoundSample>("SpaceShipMoving");
	sample->SetLoop(true);
	sample->SetVolume(5.0f);

	UpdateDirection();
}

void UPlayerMovementComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	ComputeAcceleration(_deltaTime);
	Move(_deltaTime);
	Rotate(_deltaTime);
}

void UPlayerMovementComponent::Move(const float _deltaTime)
{
	if (!owner || !canMove) return;

	if (velocity.x > maxVelocity.x) velocity.x = maxVelocity.x;
	else if (velocity.x < -maxVelocity.x) velocity.x = -maxVelocity.x;

	if (velocity.y > maxVelocity.y) velocity.y = maxVelocity.y;
	else if (velocity.y < -maxVelocity.y) velocity.y = -maxVelocity.y;

	owner->SetLocation(owner->GetLocation() + velocity);
}

void UPlayerMovementComponent::Rotate(const float _deltaTime)
{
	if (!canRotate) return;

	const float _rotationFactor = rotateLeft ? -1.0f : 1.0f;

	currentAngle += degreesToRotate * _rotationFactor * _deltaTime * rotateSpeed;
	if (currentAngle >= 360.0f)
	{
		currentAngle -= 360.0f;
	}
	else if (currentAngle <= 0.0f)
	{
		currentAngle = 360.0f;
	}

	UpdateDirection();

	owner->SetRotation(Angle(degrees(currentAngle)));
}

void UPlayerMovementComponent::UpdateDirection()
{
	const float _rad = DegToRad(currentAngle);
	direction.x = cos(_rad);
	direction.y = sin(_rad);
}

void UPlayerMovementComponent::ComputeAcceleration(const float _deltaTime)
{
	if (!canAccelerate) return;

	acceleration.x += _deltaTime * accelerationFactor;
	acceleration.y += _deltaTime * accelerationFactor;

	// Calcul l'offset et le cap pour ne pas aller au dela de la vitesse max
	velocity.x += direction.x * acceleration.x * _deltaTime;
	velocity.y += direction.y * acceleration.y * _deltaTime;
}
