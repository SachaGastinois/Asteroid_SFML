#pragma once
#include "Component.h"
#include "VertexObject.h"

class AActor;

class UVertexComponent : public UComponent
{
	VertexObject* vertex;

public:
	FORCEINLINE VertexObject* GetVertex() const
	{
		return vertex;
	}

	FORCEINLINE virtual UComponent* Clone(AActor* _owner) const override
	{
		return new UVertexComponent(_owner, *this);
	}

public:
	UVertexComponent(AActor* _owner, const u_int& _count, const PrimitiveType& _type = PrimitiveType::Points);
	UVertexComponent(AActor* _owner, const UVertexComponent& _other);
	~UVertexComponent();

};