#pragma once
#include "Component.h"
#include "ShapeObject.h"

class AActor;

class UStaticMeshComponent : public UComponent
{
	u_int renderMeshToken;
	ShapeObject* shape;

public:
	FORCEINLINE void SetShape(ShapeObject* _shape)
	{
		shape = _shape;
	}
	FORCEINLINE u_int GetRenderMeshToken() const
	{
		return renderMeshToken;
	}
	FORCEINLINE ShapeObject* GetShape() const
	{
		return shape;
	}
	FORCEINLINE virtual UComponent* Clone(AActor* _owner) const override
	{
		return new UStaticMeshComponent(_owner, *this);
	}

public:
	UStaticMeshComponent(AActor* _owner, const CircleShapeData& _data);
	UStaticMeshComponent(AActor* _owner, const RectangleShapeData& _data);
	UStaticMeshComponent(AActor* _owner, const UStaticMeshComponent& _other);
	~UStaticMeshComponent();

	virtual void Construct() override;
	virtual void Deconstruct() override;

	virtual void Tick(const float _deltaTime) override;

	void SetOriginAtMiddle();
	void RenderMesh(RenderWindow& _window);
};