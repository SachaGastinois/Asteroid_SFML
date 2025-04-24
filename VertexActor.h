#pragma once
#include "Actor.h"
#include "VertexComponent.h"

class AVertexActor : public AActor
{
	UVertexComponent* vertex;
	u_int renderMeshToken;

public:
	FORCEINLINE Vertex& GetVertexByIndex(const u_int& _index)
	{
		return vertex->GetVertex()->GetVertexByIndex(_index);
	}

public:
	AVertexActor(Level* _level, const u_int& _count, const PrimitiveType& _type = PrimitiveType::Points,
				const string& _name = "VertexActor");
	AVertexActor(const AVertexActor& _other);

	virtual void Construct() override;
	virtual void Deconstruct() override;
	virtual void RenderVertices(RenderWindow& _window);
};