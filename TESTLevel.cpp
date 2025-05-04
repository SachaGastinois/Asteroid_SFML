#include "TESTLevel.h"
#include "PlayerPawn.h"
#include "CircleActor.h"
#include "CUSTOMGameMode.h"
#include "CanvasWidget.h"
#include "ImageWidget.h"
#include "LabelWidget.h"
#include "ButtonWidget.h"

using namespace UI;

TESTLevel::TESTLevel(const string& _levelName) : Level(_levelName)
{

}

void TESTLevel::InitLevel()
{
	Super::InitLevel();

	HUD* _hud = GetGameMode()->GetHUD();

	mainMenuCanvas = _hud->SpawnWidget<UI::CanvasWidget>("MainMenuCanvas");
	optionCanvas = _hud->SpawnWidget<UI::CanvasWidget>("OptionCanvas");
	

	InitMainMenu(_hud);
	InitOptionMenu(_hud);

	OpenMenu(mainMenuCanvas, optionCanvas);
}

void TESTLevel::InitMainMenu(HUD* _hud)
{
	const Vector2f& _windowSize = GetWindowSize();

	mainMenuCanvas->SetSize(CAST(Vector2f, _windowSize));

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("ASTEROID", "MainMenuLabel", Screen);
	_title->SetCharacterSize(75);
	_title->SetOriginAtMiddle();
	_title->SetLocation(Vector2f(_windowSize.x / 2.0f, _windowSize.y * 0.1f));
	_title->SetZOrder(1);

	ButtonWidget* _button = _hud->SpawnWidget<ButtonWidget>(RectangleShapeData(Vector2f(100, 100)), "MainMenuButton");
	_button->SetLocation(Vector2f(_windowSize.x / 2.0f, _windowSize.y * 0.8f));
	_button->SetOriginAtMiddle();
	_button->SetZOrder(2);
	_button->BindOnClickAction([&]() { OpenMenu(optionCanvas, mainMenuCanvas); });

	mainMenuCanvas->AddChild(_title);
	mainMenuCanvas->AddChild(_button);
}

void TESTLevel::InitOptionMenu(HUD* _hud)
{
	const Vector2f& _windowSize = GetWindowSize();

	optionCanvas->SetSize(CAST(Vector2f, _windowSize));

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("OPTION", "OptionLabel", Screen);
	_title->SetCharacterSize(75);
	_title->SetOriginAtMiddle();
	_title->SetLocation(Vector2f(_windowSize.x / 2.0f, _windowSize.y * 0.1f));
	_title->SetZOrder(1);

	ButtonWidget* _button = _hud->SpawnWidget<ButtonWidget>(RectangleShapeData(Vector2f(100, 100)), "OptionButton");
	_button->SetLocation(_windowSize * 0.8f);
	_button->SetOriginAtMiddle();
	_button->SetZOrder(2);
	_button->BindOnClickAction([&]() 
	{ 
		OpenMenu(mainMenuCanvas, optionCanvas); 
	});
	optionCanvas->AddChild(_title);
	optionCanvas->AddChild(_button);
}

void TESTLevel::OpenMenu(UI::CanvasWidget* _canvaToOpen, UI::CanvasWidget* _canvaToClose)
{
	LOG(Warning, "Open " + _canvaToOpen->GetName() + " and Close " + _canvaToClose->GetName());

	GetGameMode()->GetHUD()->AddToViewport(_canvaToOpen);
	_canvaToOpen->SetVisibility(VisibilityType::Visible);
	
	GetGameMode()->GetHUD()->RemoveFromViewport(_canvaToClose);
	_canvaToClose->SetVisibility(VisibilityType::Hidden);
}
