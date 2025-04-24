#include "VertexComponent.h"

UVertexComponent::UVertexComponent(AActor* _owner, const u_int& _count, const PrimitiveType& _type) 
							   : UComponent(_owner)
{
	vertex = new VertexObject(_count, _type);
}

UVertexComponent::UVertexComponent(AActor* _owner, const UVertexComponent& _other) : UComponent(_owner)
{
	vertex = new VertexObject(*_other.vertex);
}

UVertexComponent::~UVertexComponent()
{
	delete vertex;
}