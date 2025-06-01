#pragma once

#include "Component.h"

struct FLifeData
{
	int maxLife;
	int currentLife;
	function<void()> onDeathCallback;

	FLifeData() = default;
	FLifeData(const int _maxLife, const int _currentLife, const function<void()>& _onDeathCallback)
	{
		maxLife = _maxLife;
		currentLife = _currentLife;
		onDeathCallback = _onDeathCallback;
	}
};

class ULifeComponent : public UComponent
{
	FLifeData data;

	bool canBeAttacked;
	float currentTime;
	float maxTime;

public:
	FORCEINLINE virtual UComponent* Clone(AActor* _owner) const override
	{
		return new ULifeComponent(_owner, *this);
	}
	FORCEINLINE void SetCanBeAttacked(const bool _status)
	{
		canBeAttacked = _status;
	}
	FORCEINLINE void SetCurrentLife(const int _life)
	{
		data.currentLife = _life;
	}
	FORCEINLINE bool GetCanBeAttacked() const
	{
		return canBeAttacked;
	}
	FORCEINLINE FLifeData GetLifeData() const
	{
		return data;
	}
public:
	ULifeComponent(AActor* _owner, const FLifeData& _data);
	ULifeComponent(AActor* _owner, const ULifeComponent& _other);
protected:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;

	void UpdateTime(const float _deltaTime);
public:
	void AddLife(const int _lifeToAdd);
	void RemoveLife();
};

