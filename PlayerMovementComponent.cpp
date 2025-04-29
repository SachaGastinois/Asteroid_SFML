#include "PlayerMovementComponent.h"
#include "Actor.h"
#include "PlayerPawn.h"

UPlayerMovementComponent::UPlayerMovementComponent(AActor* _owner) : UComponent(_owner)
{

}

UPlayerMovementComponent::UPlayerMovementComponent(AActor* _owner, 
	const UPlayerMovementComponent& _other) : UComponent(_owner, _other)
{

}

void UPlayerMovementComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UPlayerMovementComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	Move(_deltaTime);
}

void UPlayerMovementComponent::Move(const float _deltaTime)
{
	if (!owner) return;

	deltaTime = _deltaTime;

	if (velocity.x > maxVelocity.x) velocity.x = maxVelocity.x;
	else if (velocity.x < -maxVelocity.x) velocity.x = -maxVelocity.x;

	if (velocity.y > maxVelocity.y) velocity.y = maxVelocity.y;
	else if (velocity.y < -maxVelocity.y) velocity.y = -maxVelocity.y;

	owner->Move(velocity);
	//LOG(Warning, "Move Forward");
}

void UPlayerMovementComponent::MoveLeft()
{
	Rotate(-10.0f);
	//LOG(Warning, "Rotate Left");
}

void UPlayerMovementComponent::MoveRight()
{
	Rotate(10.0f);
	//LOG(Warning, "Rotate Right");
}

void UPlayerMovementComponent::Rotate(const float _degree)
{
	currentAngle += _degree;
	if (currentAngle > 360.0f)
	{
		currentAngle -= 360.0f;
	}
	else if (currentAngle < 0.0f)
	{
		currentAngle = 360.0f;
	}

	owner->Rotate(Angle(degrees(_degree)));
}

void UPlayerMovementComponent::UpdateDirection()
{
	const float _rad = DegToRad(currentAngle);
	direction.x = cos(_rad);
	direction.y = sin(_rad);
}

void UPlayerMovementComponent::ComputeAcceleration()
{
	UpdateDirection();

	acceleration.x += 0.5f;
	acceleration.y += 0.5f;

	// Calcul l'offset et le cap pour ne pas aller au dela de la vitesse max
	velocity.x += direction.x * acceleration.x * deltaTime;
	velocity.y += direction.y * acceleration.y * deltaTime;
}
