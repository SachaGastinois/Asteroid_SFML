#pragma once
#include "Core.h"

class UComponent : public UCore
{
protected:
	class AActor* owner;

public:
	FORCEINLINE AActor* GetOwner() const
	{
		return owner;
	}

public:
	UComponent(AActor* _owner);
	UComponent(AActor* _owner, const UComponent& _other);
	virtual ~UComponent() = default;

public:
	virtual void Construct() override;
	virtual void Deconstruct() override;
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override {};
	virtual void BeginDestroy() override {};

	virtual UComponent* Clone(AActor* _owner) const = 0;
};