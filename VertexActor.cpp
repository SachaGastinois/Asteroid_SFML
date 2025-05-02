#include "VertexActor.h"
#include "Level.h"

using namespace Camera;

AVertexActor::AVertexActor(Level* _level, const u_int& _count, const PrimitiveType& _type, const string& _name) : AActor(_level, _name)
{
	vertex = CreateDefaultSubobject<UVertexComponent>(_count, _type);
	renderMeshToken = -1;
}

AVertexActor::AVertexActor(const AVertexActor& _other) : AActor(_other)
{
	vertex = CreateDefaultSubobject<UVertexComponent>(*_other.vertex);
	renderMeshToken = _other.renderMeshToken;
}

void AVertexActor::Construct()
{
	Super::Construct();

	const FRenderData& _data = FRenderData(bind(&AVertexActor::RenderVertices, this, _1));
	renderMeshToken = level->GetCameraManager().BindOnRenderWindow(_data);
}

void AVertexActor::Deconstruct()
{
	Super::Deconstruct();
	level->GetCameraManager().UnbindOnRenderWindow(renderMeshToken);
}


void AVertexActor::RenderVertices(RenderWindow& _window)
{
	_window.draw(*vertex->GetVertex()->GetDrawable());
}