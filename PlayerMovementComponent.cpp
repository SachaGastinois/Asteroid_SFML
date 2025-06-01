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

	deltaTime = 0.0f;
	rotateSpeed = 30.0f;

	currentAngle = 270.0f;
	friction = 0.95f;

	maxVelocity = Vector2f(0.5f, 0.5f);
	acceleration = Vector2f();
	velocity = Vector2f();
	direction = Vector2f(0.0f, 0.0f);
}

UPlayerMovementComponent::UPlayerMovementComponent(AActor* _owner, 
	const UPlayerMovementComponent& _other) : UComponent(_owner, _other)
{
	canMove = _other.canMove;
	velocity = _other.velocity;
	deltaTime = _other.deltaTime;
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

	sample = owner->GetLevel()->SpawnActor<SoundSample>("SpaceShipMoving.mp3");
	sample->SetLoop(false);
	owner->GetLevel()->GetAudioManager().RegisterSample(sample);
	sample->SetVolume(5.0f);
}

void UPlayerMovementComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	Move(_deltaTime);

	//LOG(Display, to_string(currentAngle));

}

void UPlayerMovementComponent::Move(const float _deltaTime)
{
	if (!owner || !canMove) return;


	deltaTime = _deltaTime;

	if (velocity.x > maxVelocity.x) velocity.x = maxVelocity.x;
	else if (velocity.x < -maxVelocity.x) velocity.x = -maxVelocity.x;

	if (velocity.y > maxVelocity.y) velocity.y = maxVelocity.y;
	else if (velocity.y < -maxVelocity.y) velocity.y = -maxVelocity.y;

	owner->SetLocation(owner->GetLocation() + velocity);
}

void UPlayerMovementComponent::Rotate(const float _degree)
{
	currentAngle += _degree;
	if (currentAngle >= 360.0f)
	{
		currentAngle -= 360.0f;
	}
	else if (currentAngle <= 0.0f)
	{
		currentAngle = 360.0f;
	}

	owner->SetRotation(Angle(degrees(currentAngle)));
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
