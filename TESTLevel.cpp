#include "TESTLevel.h"
#include "PlayerPawn.h"
#include "CircleActor.h"
#include "CUSTOMGameMode.h"
#include "CanvasWidget.h"
#include "ImageWidget.h"

using namespace UI;

TESTLevel::TESTLevel(const string& _levelName) : Level(_levelName)
{

}

void TESTLevel::InitLevel()
{
	Super::InitLevel();

	HUD* _hud = GetGameMode()->GetHUD();

	UI::CanvasWidget* canvas = _hud->SpawnWidget<UI::CanvasWidget>();
	canvas->SetSize(CAST(Vector2f, GetWindowSize()));

	ImageWidget* _image = _hud->SpawnWidget<ImageWidget>(CircleShapeData(50.0f));
	canvas->AddChild(_image);

	AActor* _actor = SpawnActor<APlayerPawn>();
	ACircleActor* _circle = SpawnActor<ACircleActor>(50.0f);
	_circle->SetLocation(Vector2f(100.0f, 100.0f));
	_actor->SetLocation(GetWindowSize() / 2.0f);

	GetGameMode()->GetHUD()->AddToViewport(canvas);

}
