#include "LifeComponent.h"
#include "ClassicModeLevel.h"
#include "UFO.h"
#include "Asteroid.h"
#include "AudioManager.h"

ULifeComponent::ULifeComponent(AActor* _owner, const FLifeData& _data) : UComponent(_owner)
{
	data = _data;
	currentTime = 0.0f;
	maxTime = 1.0f;
	canBeAttacked = true;
}

ULifeComponent::ULifeComponent(AActor* _owner, const ULifeComponent& _other) : UComponent(_owner, _other)
{
	data = _other.data;
	currentTime = _other.currentTime;
	maxTime = _other.maxTime;
	canBeAttacked = _other.canBeAttacked;
}

void ULifeComponent::BeginPlay()
{
	Super::BeginPlay();

	explosionSample = owner->GetLevel()->SpawnSample<SoundSample>("Explosion");
	explosionSample->Stop();
	explosionSample->SetVolume(5.0f);

	hitSample = owner->GetLevel()->SpawnSample<SoundSample>("PlayerHurt");
	hitSample->Stop();
	hitSample->SetVolume(5.0f);
}

void ULifeComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	UpdateTime(_deltaTime);
}

void ULifeComponent::UpdateTime(const float _deltaTime)
{
	if (canBeAttacked) return;

	currentTime += _deltaTime;

	if (currentTime >= maxTime)
	{
		currentTime = 0.0f;
		canBeAttacked = true;
	}
}

void ULifeComponent::AddLife(const int _lifeToAdd)
{
	data.currentLife += _lifeToAdd;

	if (data.currentLife >= data.maxLife)
	{
		data.currentLife = data.maxLife;
	}
}

void ULifeComponent::RemoveLife()
{
	if (!canBeAttacked) return;

	data.currentLife--;

	canBeAttacked = false;

	if(Cast<AUFO>(owner) || Cast<AAsteroid>(owner))
	{
		if (UClassicModeLevel* _level = Cast<UClassicModeLevel>(owner->GetLevel()))
		{
			_level->DecrementEntityLeft();
		}
	}
	if (data.currentLife <= 0)
	{
		explosionSample->Play();
		data.onDeathCallback();
	}
	else
	{
		hitSample->Play();
	}
}