#pragma once
#include "Core.h"

class UComponent : public UCore
{
protected:
	class AActor* owner;
	UComponent* attachmentComponent;

public:
	FORCEINLINE AActor* GetOwner() const
	{
		if (!owner) return nullptr;

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
	void SetupAttachment(UComponent* _component);

	virtual UComponent* Clone(AActor* _owner) const = 0;
};