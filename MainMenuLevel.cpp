#include "MainMenuLevel.h"
#include "PlayerPawn.h"
#include "CircleActor.h"
#include "CUSTOMGameMode.h"
#include "CanvasWidget.h"
#include "ImageWidget.h"
#include "LabelWidget.h"
#include "ButtonWidget.h"

using namespace UI;

UMainMenuLevel::UMainMenuLevel(const string& _levelName) : Level(_levelName)
{
	mainMenuCanvas = nullptr;
	optionCanvas = nullptr;
	leaderBoardCanvas = nullptr;
	startCanvas = nullptr;
	creditCanvas = nullptr;
}

void UMainMenuLevel::InitLevel()
{
	Super::InitLevel();

	HUD* _hud = GetGameMode()->GetHUD();

	mainMenuCanvas = _hud->SpawnWidget<UI::CanvasWidget>("MainMenuCanvas");
	optionCanvas = _hud->SpawnWidget<UI::CanvasWidget>("OptionCanvas");
	

	InitMainMenu(_hud);
	InitOptionMenu(_hud);

	OpenMenu(mainMenuCanvas, optionCanvas);
}

void UMainMenuLevel::InitMainMenu(HUD* _hud)
{
	const Vector2f& _windowSize = GetWindowSize();

	mainMenuCanvas->SetSize(CAST(Vector2f, _windowSize));

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("ASTEROID", "MainMenuLabel", Screen);
	_title->SetLocation(Vector2f(_windowSize.x * 0.5f, _windowSize.y * 0.2f));
	_title->SetFont("Daydream", TTF);
	_title->SetCharacterSize(75);
	_title->SetOriginAtMiddle();
	_title->SetZOrder(1);

	mainMenuCanvas->AddChild(_title);

	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);
	const Vector2f& _size = Vector2f(200.0f, 50.0f);

	//////////////////////////
	///		Play
	//////////////////////////

	const Vector2f& _playLocation = Vector2f(_windowSize.x * 0.3f, _windowSize.y * 0.8f);

	const FButtonAndLabelData& _playData = FButtonAndLabelData("PLAY", "PlayLabel", "PlayButton", "", _playLocation,
		_size, _fontData, 25, 2);

	ButtonWidget* _playButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _playData);
	_playButton->BindOnClickAction([&]() { OpenMenu(optionCanvas, mainMenuCanvas); });

	//////////////////////////
	///		LeaderBoard
	//////////////////////////

	const Vector2f& _leaderBoardLocation = Vector2f(_windowSize.x * 0.4f, _windowSize.y * 0.9);

	const FButtonAndLabelData& _leaderBoardData = FButtonAndLabelData("LEADERBOARD", "LeaderBoardLabel", "LeaderBoardButton",
		"", _leaderBoardLocation, { 200.0f, 40.0f }, _fontData, 15, 2);

	ButtonWidget* _leaderBoardButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _leaderBoardData);
	_leaderBoardButton->BindOnClickAction([&]() { OpenMenu(optionCanvas, mainMenuCanvas); });

	//////////////////////////
	///		Credits
	//////////////////////////

	const Vector2f& _creditLocation = Vector2f(_windowSize.x * 0.6f, _windowSize.y * 0.9f);

	const FButtonAndLabelData& _creditData = FButtonAndLabelData("CREDIT", "CreditLabel", "CreditButton",
		"", _creditLocation, { 150.0f, 40.0f }, _fontData, 15, 2);

	ButtonWidget* _creditButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _creditData);
	_creditButton->BindOnClickAction([&]() { OpenMenu(optionCanvas, mainMenuCanvas); });

	//////////////////////////
	///		Options
	//////////////////////////

	const Vector2f& _optionLocation = Vector2f(_windowSize.x * 0.5f, _windowSize.y * 0.8f);

	const FButtonAndLabelData& _optionData = FButtonAndLabelData("OPTION", "OptionLabel", "OptionButton",
		"", _optionLocation, _size, _fontData, 25, 2);

	ButtonWidget* _optionButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _optionData);
	_optionButton->BindOnClickAction([&]() { OpenMenu(optionCanvas, mainMenuCanvas); });

	//////////////////////////
	///		Quit
	//////////////////////////

	const Vector2f& _quitLocation = Vector2f(_windowSize.x * 0.7f, _windowSize.y * 0.8f);

	const FButtonAndLabelData& _quitData = FButtonAndLabelData("QUIT", "QuitLabel", "QuitButton",
		"", _quitLocation, _size, _fontData, 25, 2);

	ButtonWidget* _quitButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _quitData);
	_quitButton->BindOnClickAction([&]() { OpenMenu(optionCanvas, mainMenuCanvas); });
}

void UMainMenuLevel::InitOptionMenu(HUD* _hud)
{
	const Vector2f& _windowSize = GetWindowSize();

	optionCanvas->SetSize(CAST(Vector2f, _windowSize));

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("OPTION", "OptionTitleLabel", Screen);
	_title->SetCharacterSize(75);
	_title->SetOriginAtMiddle();
	_title->SetLocation(Vector2f(_windowSize.x / 2.0f, _windowSize.y * 0.1f));
	_title->SetZOrder(1);

	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);
	const Vector2f& _size = Vector2f(200.0f, 50.0f);

	optionCanvas->AddChild(_title);
	//////////////////////////
	///		Back
	//////////////////////////

	const Vector2f& _backLocation = Vector2f(_windowSize.x * 0.9f, _windowSize.y * 0.9f);

	const FButtonAndLabelData& _backData = FButtonAndLabelData("BACK", "BackOptionLabel", "BackOptionButton",
		"", _backLocation, { 100.0f, 100.0f }, _fontData, 25, 2);

	ButtonWidget* _quitButton = InitButtonAndLabelData(_hud, optionCanvas, _backData);
	_quitButton->BindOnClickAction([&]() { OpenMenu(mainMenuCanvas, optionCanvas); });

}

void UMainMenuLevel::InitLeaderBoardMenu(HUD* _hud)
{
}

void UMainMenuLevel::InitStartMenu(HUD* _hud)
{
}

void UMainMenuLevel::InitCreditMenu(HUD* _hud)
{
}

ButtonWidget* UMainMenuLevel::InitButtonAndLabelData(HUD* _hud, UI::CanvasWidget* _canva, const FButtonAndLabelData& _data)
{
	const Vector2f& _windowSize = GetWindowSize();

	ALabelWidget* _label = _hud->SpawnWidget<ALabelWidget>(_data.text, _data.labelName, Screen);
	_label->SetLocation(_data.location);
	_label->SetFont(_data.fontData.first, _data.fontData.second);
	_label->SetCharacterSize(_data.characterSize);
	_label->SetOriginAtMiddle();
	_label->SetZOrder(_data.zOrder);

	ButtonWidget* _button = _hud->SpawnWidget<ButtonWidget>(RectangleShapeData(_data.size), _data.buttonName, Screen);
	_button->SetLocation(_data.location - _data.size / 2.0f);
	_button->SetOriginAtMiddle();
	_button->SetZOrder(_data.zOrder - 1);
	_button->BindOnClickAction([&]() { OpenMenu(optionCanvas, mainMenuCanvas); });

	_canva->AddChild(_label);
	_canva->AddChild(_button);

	return _button;
}

void UMainMenuLevel::OpenMenu(UI::CanvasWidget* _canvaToOpen, UI::CanvasWidget* _canvaToClose)
{
	LOG(Warning, "Open " + _canvaToOpen->GetName() + " and Close " + _canvaToClose->GetName());

	GetGameMode()->GetHUD()->AddToViewport(_canvaToOpen);
	_canvaToOpen->SetVisibility(VisibilityType::Visible);
	
	GetGameMode()->GetHUD()->RemoveFromViewport(_canvaToClose);
	_canvaToClose->SetVisibility(VisibilityType::Hidden);
}
