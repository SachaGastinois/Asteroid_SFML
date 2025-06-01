#pragma once

#include "Component.h"

struct FSocketData
{
	AActor* socket;
	Vector2f relativeLoc;
	bool isActive;

	FSocketData(AActor* _socket, const Vector2f& _relativeLoc)
	{
		socket = _socket;
		relativeLoc = _relativeLoc;
		isActive = true;
	}
};

class UShootComponent : public UComponent
{
	vector<FSocketData> sockets;

public:
	FORCEINLINE void SetSockets(const vector<FSocketData>& _sockets)
	{
		sockets = _sockets;
	}
	FORCEINLINE vector<FSocketData>& GetSockets()
	{
		return sockets;
	}
	FORCEINLINE virtual UComponent* Clone(AActor* _owner) const override
	{
		return new UShootComponent(_owner, *this);
	}
public:
	UShootComponent(AActor* _owner);
	UShootComponent(AActor* _owner, const vector<FSocketData>& _sockets);
	UShootComponent(AActor* _owner, const UShootComponent& _other);

private:
	virtual void BeginPlay() override;
	virtual void Tick(const float _deltaTime) override;

	void UpdateSocket();

public:
	void Shoot();
};

