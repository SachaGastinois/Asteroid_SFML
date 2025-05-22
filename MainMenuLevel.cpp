#include "MainMenuLevel.h"
#include "PlayerPawn.h"
#include "CircleActor.h"
#include "CUSTOMGameMode.h"
#include "CanvasWidget.h"
#include "ImageWidget.h"
#include "LabelWidget.h"
#include "ButtonWidget.h"
#include "LevelManager.h"
#include "ClassicModeLevel.h"

using namespace UI;

UMainMenuLevel::UMainMenuLevel(const string& _levelName) : UUtilityLevel(_levelName)
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

	windowSize = GetWindowSize();

	HUD* _hud = GetGameMode()->GetHUD();
	
	mainMenuCanvas = _hud->SpawnWidget<UI::CanvasWidget>("MainMenuCanvas");
	optionCanvas = _hud->SpawnWidget<UI::CanvasWidget>("OptionCanvas");
	leaderBoardCanvas = _hud->SpawnWidget<UI::CanvasWidget>("LeaderBoardCanvas");
	startCanvas = _hud->SpawnWidget<UI::CanvasWidget>("StartCanvas");
	creditCanvas = _hud->SpawnWidget<UI::CanvasWidget>("CreditCanvas");

	InitMainMenu(_hud);
	InitOptionMenu(_hud);
	InitLeaderBoardMenu(_hud);
	InitStartMenu(_hud);
	InitCreditMenu(_hud);
	
	OpenMenu(mainMenuCanvas, mainMenuCanvas);
}

void UMainMenuLevel::InitMainMenu(HUD* _hud)
{
	mainMenuCanvas->SetSize(CAST(Vector2f, windowSize));

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("ASTEROID", "MainMenuLabel", Screen);
	_title->SetLocation(Vector2f(windowSize.x * 0.5f, windowSize.y * 0.2f));
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

	const Vector2f& _playLocation = Vector2f(windowSize.x * 0.3f, windowSize.y * 0.8f);

	const FButtonAndLabelData& _playData = FButtonAndLabelData("PLAY", "PlayLabel", "PlayButton", "", _playLocation,
		_size, _fontData, 25, 2);

	ButtonWidget* _playButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _playData);
	_playButton->BindOnClickAction([&]() { OpenMenu(startCanvas, mainMenuCanvas); });

	//////////////////////////
	///		LeaderBoard
	//////////////////////////

	const Vector2f& _leaderBoardLocation = Vector2f(windowSize.x * 0.4f, windowSize.y * 0.9);

	const FButtonAndLabelData& _leaderBoardData = FButtonAndLabelData("LEADERBOARD", "LeaderBoardLabel", "LeaderBoardButton",
		"", _leaderBoardLocation, { 200.0f, 40.0f }, _fontData, 15, 2);

	ButtonWidget* _leaderBoardButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _leaderBoardData);
	_leaderBoardButton->BindOnClickAction([&]() { OpenMenu(leaderBoardCanvas, mainMenuCanvas); });

	//////////////////////////
	///		Credits
	//////////////////////////

	const Vector2f& _creditLocation = Vector2f(windowSize.x * 0.6f, windowSize.y * 0.9f);

	const FButtonAndLabelData& _creditData = FButtonAndLabelData("CREDIT", "CreditLabel", "CreditButton",
		"", _creditLocation, { 150.0f, 40.0f }, _fontData, 15, 2);

	ButtonWidget* _creditButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _creditData);
	_creditButton->BindOnClickAction([&]() { OpenMenu(creditCanvas, mainMenuCanvas); });

	//////////////////////////
	///		Options
	//////////////////////////

	const Vector2f& _optionLocation = Vector2f(windowSize.x * 0.5f, windowSize.y * 0.8f);

	const FButtonAndLabelData& _optionData = FButtonAndLabelData("OPTION", "OptionLabel", "OptionButton",
		"", _optionLocation, _size, _fontData, 25, 2);

	ButtonWidget* _optionButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _optionData);
	_optionButton->BindOnClickAction([&]() { OpenMenu(optionCanvas, mainMenuCanvas); });

	//////////////////////////
	///		Quit
	//////////////////////////

	const Vector2f& _quitLocation = Vector2f(windowSize.x * 0.7f, windowSize.y * 0.8f);

	const FButtonAndLabelData& _quitData = FButtonAndLabelData("QUIT", "QuitLabel", "QuitButton",
		"", _quitLocation, _size, _fontData, 25, 2);

	ButtonWidget* _quitButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _quitData);
	_quitButton->BindOnClickAction([&]() { Unload(); });
}

void UMainMenuLevel::InitOptionMenu(HUD* _hud)
{
	if (!optionCanvas || !mainMenuCanvas) return;
	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);

	optionCanvas->SetSize(windowSize);

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("OPTION", "OptionTitleLabel", Screen);
	_title->SetCharacterSize(50);
	_title->SetFont(_fontData.first, _fontData.second);
	_title->SetOriginAtMiddle();
	_title->SetLocation(Vector2f(windowSize.x / 2.0f, windowSize.y * 0.1f));
	_title->SetZOrder(1);


	optionCanvas->AddChild(_title);

	//////////////////////////
	///		Back
	//////////////////////////

	const Vector2f& _backLocation = Vector2f(windowSize.x * 0.9f, windowSize.y * 0.9f);

	const FButtonAndLabelData& _backData = FButtonAndLabelData("BACK", "BackOptionLabel", "BackOptionButton",
		"", _backLocation, { 150.0f, 50.0f }, _fontData, 25, 2);

	ButtonWidget* _backButton = InitButtonAndLabelData(_hud, optionCanvas, _backData);
	_backButton->BindOnClickAction([&]() { OpenMenu(mainMenuCanvas, optionCanvas); });
}

void UMainMenuLevel::InitLeaderBoardMenu(HUD* _hud)
{
	if (!leaderBoardCanvas || !mainMenuCanvas) return;
	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);

	leaderBoardCanvas->SetSize(windowSize);

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("LEADERBOARD", "LeaderBoardTitleLabel", Screen);
	_title->SetCharacterSize(50);
	_title->SetFont(_fontData.first, _fontData.second);
	_title->SetOriginAtMiddle();
	_title->SetLocation(Vector2f(windowSize.x / 2.0f, windowSize.y * 0.1f));
	_title->SetZOrder(1);


	leaderBoardCanvas->AddChild(_title);

	//////////////////////////
	///		Back
	//////////////////////////

	const Vector2f& _backLocation = Vector2f(windowSize.x * 0.9f, windowSize.y * 0.9f);

	const FButtonAndLabelData& _backData = FButtonAndLabelData("BACK", "BackLeaderBoardLabel", "BackLeaderBoardButton",
		"", _backLocation, { 150.0f, 50.0f }, _fontData, 25, 2);

	ButtonWidget* _backButton = InitButtonAndLabelData(_hud, leaderBoardCanvas, _backData);
	_backButton->BindOnClickAction([&]() { OpenMenu(mainMenuCanvas, leaderBoardCanvas); });
}

void UMainMenuLevel::InitStartMenu(HUD* _hud)
{
	if (!startCanvas || !mainMenuCanvas) return;
	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);

	startCanvas->SetSize(windowSize);

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("START", "StartTitleLabel", Screen);
	_title->SetCharacterSize(50);
	_title->SetFont(_fontData.first, _fontData.second);
	_title->SetOriginAtMiddle();
	_title->SetLocation(Vector2f(windowSize.x * 0.5f, windowSize.y * 0.1f));
	_title->SetZOrder(1);

	startCanvas->AddChild(_title);

	//////////////////////////
	///		Controls
	//////////////////////////

	ALabelWidget* _controlsLabel = _hud->SpawnWidget<ALabelWidget>("Controls", "ControlsStartLabel", Screen);
	_controlsLabel->SetCharacterSize(25);
	_controlsLabel->SetFont(_fontData.first, _fontData.second);
	_controlsLabel->SetOriginAtMiddle();
	_controlsLabel->SetLocation(Vector2f(windowSize.x * 0.7f, windowSize.y * 0.3f));
	_controlsLabel->SetZOrder(1);

	startCanvas->AddChild(_controlsLabel);

	//////////////////////////
	///		Echap
	//////////////////////////

	AImageWidget* _controlsEchapImage = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 100.0f, 100.0f },
		"Widgets/MainMenu/Start/Keyboard_SpriteSheet", PNG, false, IntRect({ 0, 0 }, { 32, 32 })),
		"ControlsEchapImage", Screen);
	_controlsEchapImage->SetOriginAtMiddle();
	_controlsEchapImage->SetLocation(Vector2f(windowSize.x * 0.56f, windowSize.y * 0.4f));
	_controlsEchapImage->SetZOrder(1);

	startCanvas->AddChild(_controlsEchapImage);

	ALabelWidget* _controlsEchapLabel = _hud->SpawnWidget<ALabelWidget>("Pause", "ControlsEchapLabel", Screen);
	_controlsEchapLabel->SetCharacterSize(10);
	_controlsEchapLabel->SetFont(_fontData.first, _fontData.second);
	_controlsEchapLabel->SetOriginAtMiddle();
	_controlsEchapLabel->SetLocation(Vector2f(windowSize.x * 0.6f, windowSize.y * 0.55f));
	_controlsEchapLabel->SetZOrder(1);

	startCanvas->AddChild(_controlsEchapLabel);

	//////////////////////////
	///		Z 
	//////////////////////////

	AImageWidget* _controlsZImage = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 100.0f, 100.0f },
		"Widgets/MainMenu/Start/Keyboard_SpriteSheet", PNG, false, IntRect({ 32, 0 }, { 32, 32 })),
		"ControlsZImage", Screen);
	_controlsZImage->SetOriginAtMiddle();
	_controlsZImage->SetLocation(Vector2f(windowSize.x * 0.8f, windowSize.y * 0.4f));
	_controlsZImage->SetZOrder(1);

	startCanvas->AddChild(_controlsZImage);

	ALabelWidget* _controlsZLabel = _hud->SpawnWidget<ALabelWidget>("Accelerate", "ControlsZLabel", Screen);
	_controlsZLabel->SetCharacterSize(10);
	_controlsZLabel->SetFont(_fontData.first, _fontData.second);
	_controlsZLabel->SetOriginAtMiddle();
	_controlsZLabel->SetLocation(Vector2f(windowSize.x * 0.84f, windowSize.y * 0.55f));
	_controlsZLabel->SetZOrder(1);

	startCanvas->AddChild(_controlsZLabel);

	//////////////////////////
	///		Q 
	//////////////////////////

	AImageWidget* _controlsQImage = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 100.0f, 100.0f },
		"Widgets/MainMenu/Start/Keyboard_SpriteSheet", PNG, false, IntRect({ 64, 0 }, { 32, 32 })),
		"ControlsQImage", Screen);
	_controlsQImage->SetOriginAtMiddle();
	_controlsQImage->SetLocation(Vector2f(windowSize.x * 0.74f, windowSize.y * 0.6f));
	_controlsQImage->SetZOrder(1);

	startCanvas->AddChild(_controlsQImage);

	ALabelWidget* _controlsQLabel = _hud->SpawnWidget<ALabelWidget>("Rotate Left", "ControlsQLabel", Screen);
	_controlsQLabel->SetCharacterSize(10);
	_controlsQLabel->SetFont(_fontData.first, _fontData.second);
	_controlsQLabel->SetOriginAtMiddle();
	_controlsQLabel->SetLocation(Vector2f(windowSize.x * 0.78f, windowSize.y * 0.75f));
	_controlsQLabel->SetZOrder(1);

	startCanvas->AddChild(_controlsQLabel);

	//////////////////////////
	///		S
	//////////////////////////

	AImageWidget* _controlsSImage = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 100.0f, 100.0f },
		"Widgets/MainMenu/Start/Keyboard_SpriteSheet", PNG, false, IntRect({ 96, 0 }, { 32, 32 })),
		"ControlsSImage", Screen);
	_controlsSImage->SetOriginAtMiddle();
	_controlsSImage->SetLocation(Vector2f(windowSize.x * 0.6f, windowSize.y * 0.6f));
	_controlsSImage->SetZOrder(1);

	startCanvas->AddChild(_controlsSImage);

	ALabelWidget* _controlsSLabel = _hud->SpawnWidget<ALabelWidget>("OR", "ControlsSLabel", Screen);
	_controlsSLabel->SetCharacterSize(15);
	_controlsSLabel->SetFont(_fontData.first, _fontData.second);
	_controlsSLabel->SetOriginAtMiddle();
	_controlsSLabel->SetLocation(Vector2f(windowSize.x * 0.6f, windowSize.y * 0.69f));
	_controlsSLabel->SetZOrder(1);

	startCanvas->AddChild(_controlsSLabel);

	//////////////////////////
	///		D 
	//////////////////////////

	AImageWidget* _controlsDImage = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 100.0f, 100.0f },
		"Widgets/MainMenu/Start/Keyboard_SpriteSheet", PNG, false, IntRect({ 128, 0 }, { 32, 32 })),
		"ControlsDImage", Screen);
	_controlsDImage->SetOriginAtMiddle();
	_controlsDImage->SetLocation(Vector2f(windowSize.x * 0.86f, windowSize.y * 0.6f));
	_controlsDImage->SetZOrder(1);

	startCanvas->AddChild(_controlsDImage);

	ALabelWidget* _controlsDLabel = _hud->SpawnWidget<ALabelWidget>("Rotate Right", "ControlsDLabel", Screen);
	_controlsDLabel->SetCharacterSize(10);
	_controlsDLabel->SetFont(_fontData.first, _fontData.second);
	_controlsDLabel->SetOriginAtMiddle();
	_controlsDLabel->SetLocation(Vector2f(windowSize.x * 0.9f, windowSize.y * 0.75f));
	_controlsDLabel->SetZOrder(1);

	startCanvas->AddChild(_controlsDLabel);

	//////////////////////////
	///		Space Bar 
	//////////////////////////

	AImageWidget* _controlsSpaceBarImage = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({100.0f, 100.0f}, 
			"Widgets/MainMenu/Start/Keyboard_SpriteSheet", PNG, false, IntRect({160, 0},{32, 32})), 
			"ControlsSpaceBarImage", Screen);
	_controlsSpaceBarImage->SetOriginAtMiddle();
	_controlsSpaceBarImage->SetLocation(Vector2f(windowSize.x * 0.5f, windowSize.y * 0.6f));
	_controlsSpaceBarImage->SetZOrder(1);

	startCanvas->AddChild(_controlsSpaceBarImage);

	ALabelWidget* _controlsSpaceBarLabel = _hud->SpawnWidget<ALabelWidget>("Shoot", "ControlsSpacebarLabel", Screen);
	_controlsSpaceBarLabel->SetCharacterSize(10);
	_controlsSpaceBarLabel->SetFont(_fontData.first, _fontData.second);
	_controlsSpaceBarLabel->SetOriginAtMiddle();
	_controlsSpaceBarLabel->SetLocation(Vector2f(windowSize.x * 0.6f, windowSize.y * 0.75f));
	_controlsSpaceBarLabel->SetZOrder(1);

	startCanvas->AddChild(_controlsSpaceBarLabel);

	//////////////////////////
	///		Back
	//////////////////////////

	const Vector2f& _backLocation = Vector2f(windowSize.x * 0.9f, windowSize.y * 0.9f);

	const FButtonAndLabelData& _backData = FButtonAndLabelData("BACK", "BackStartLabel", "BackStartButton",
		"", _backLocation, { 150.0f, 50.0f }, _fontData, 25, 2);

	ButtonWidget* _backButton = InitButtonAndLabelData(_hud, startCanvas, _backData);
	_backButton->BindOnClickAction([&]() { OpenMenu(mainMenuCanvas, startCanvas); });


	//////////////////////////
	///		Play
	//////////////////////////

	const Vector2f& _playLocation = Vector2f(windowSize.x * 0.2f, windowSize.y * 0.5f);

	const FButtonAndLabelData& _playData = FButtonAndLabelData("PLAY", "PlayStartLabel", "PlayStartButton",
		"", _playLocation, { 200.0f, 100.0f }, _fontData, 40, 2);

	ButtonWidget* _playButton = InitButtonAndLabelData(_hud, startCanvas, _playData);
	_playButton->BindOnClickAction([&]() { M_LEVEL.SetLevel(new UClassicModeLevel("ClassicModeLevel")); });
}

void UMainMenuLevel::InitCreditMenu(HUD* _hud)
{
	if (!creditCanvas || !mainMenuCanvas) return;
	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);

	creditCanvas->SetSize(windowSize);

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("CREDIT", "CreditTitleLabel", Screen);
	_title->SetCharacterSize(50);
	_title->SetFont(_fontData.first, _fontData.second);
	_title->SetOriginAtMiddle();
	_title->SetLocation(Vector2f(windowSize.x / 2.0f, windowSize.y * 0.1f));
	_title->SetZOrder(1);


	creditCanvas->AddChild(_title);

	//////////////////////////
	///		Back
	//////////////////////////

	const Vector2f& _backLocation = Vector2f(windowSize.x * 0.9f, windowSize.y * 0.9f);

	const FButtonAndLabelData& _backData = FButtonAndLabelData("BACK", "BackCreditLabel", "BackCreditButton",
		"", _backLocation, { 150.0f, 50.0f }, _fontData, 25, 2);

	ButtonWidget* _backButton = InitButtonAndLabelData(_hud, creditCanvas, _backData);
	_backButton->BindOnClickAction([&]() { OpenMenu(mainMenuCanvas, creditCanvas); });
}


