#include "StaticMeshComponent.h"
#include "Actor.h"
#include "Level.h"

UStaticMeshComponent::UStaticMeshComponent(AActor* _owner, const CircleShapeData& _data) : UComponent(_owner)
{
	renderMeshToken = -1;
	shape = new ShapeObject(_data);
}

UStaticMeshComponent::UStaticMeshComponent(AActor* _owner, const RectangleShapeData& _data) : UComponent(_owner)
{
	renderMeshToken = -1;
	shape = new ShapeObject(_data);
}

UStaticMeshComponent::UStaticMeshComponent(AActor* _owner, const UStaticMeshComponent& _other) : UComponent(_owner) 
{
	renderMeshToken = _other.renderMeshToken;
	shape = new ShapeObject(*_other.shape);
}

UStaticMeshComponent::~UStaticMeshComponent()
{
	delete shape;
}


void UStaticMeshComponent::Construct()
{
	Super::Construct();

	if (Cast<AWidget>(owner)) return;
	const FRenderData& _data = FRenderData(bind(&UStaticMeshComponent::RenderMesh, this, _1));
	renderMeshToken = owner->GetLevel()->GetCameraManager().BindOnRenderWindow(_data);
}

void UStaticMeshComponent::Deconstruct()
{
	Super::Deconstruct();

	if (Cast<AWidget>(owner)) return;
	owner->GetLevel()->GetCameraManager().UnbindOnRenderWindow(renderMeshToken);
}

void UStaticMeshComponent::Tick(const float _deltaTime)
{
	Super::Tick(_deltaTime);

	if (!attachmentComponent || !attachmentComponent->GetOwner()) return;

	shape->SetTransform(attachmentComponent->GetOwner()->GetTransform());
}


void UStaticMeshComponent::SetOriginAtMiddle()
{
	GetOwner()->SetOrigin(shape->GetDrawable()->getGeometricCenter());
}

void UStaticMeshComponent::RenderMesh(RenderWindow& _window)
{
	if (!IsActive()) return;
	_window.draw(*shape->GetDrawable());
}