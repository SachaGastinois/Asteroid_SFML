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
#include "GIFWidget.h"
#include "LeaderBoardManager.h"
#include "MusicSample.h"
#include "SliderWidget.h"
#include "AudioManager.h"

using namespace UI;

UMainMenuLevel::UMainMenuLevel(const string& _levelName) : UUtilityLevel(_levelName)
{
	backgroundGIF = nullptr;

	mainMenuCanvas = nullptr;
	optionCanvas = nullptr;
	leaderBoardCanvas = nullptr;
	startCanvas = nullptr;
	creditCanvas = nullptr;

	windowSize = Vector2f();
}

void UMainMenuLevel::InitLevel()
{
	Super::InitLevel();

	windowSize = GetWindowSize();

	GetAudioManager().SetVolume(1.0f);

	GetCameraManager().GetCurrent()->SetLocation({ 0.0f, 0.0f });

	HUD* _hud = GetGameMode()->GetHUD();
	
	mainMenuCanvas = _hud->SpawnWidget<UI::ACanvasWidget>("MainMenuCanvas");
	optionCanvas = _hud->SpawnWidget<UI::ACanvasWidget>("OptionCanvas");
	leaderBoardCanvas = _hud->SpawnWidget<UI::ACanvasWidget>("LeaderBoardCanvas");
	startCanvas = _hud->SpawnWidget<UI::ACanvasWidget>("StartCanvas");
	creditCanvas = _hud->SpawnWidget<UI::ACanvasWidget>("CreditCanvas");

	InitBackgroundGIF(_hud);

	InitMainMenu(_hud);
	InitOptionMenu(_hud);
	InitLeaderBoardMenu(_hud);
	InitStartMenu(_hud);
	InitCreditMenu(_hud);

	OpenMenu(mainMenuCanvas, mainMenuCanvas);

	InitMainMenuTheme();

	backgroundTheme->SetVolume(5.0f);
}

void UMainMenuLevel::Update(const float _deltaTime)
{
	Super::Update(_deltaTime);

	GetCameraManager().GetCurrent()->SetActive(true);
}

void UMainMenuLevel::InitMainMenu(HUD* _hud)
{
	if (!mainMenuCanvas) return;

	mainMenuCanvas->AddChild(backgroundGIF);

	mainMenuCanvas->SetSize(windowSize);

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("ASTEROID", "MainMenuLabel", Screen);
	_title->SetLocation(Vector2f(windowSize.x * 0.5f, windowSize.y * 0.2f));
	_title->SetFont("Daydream", TTF);
	_title->SetCharacterSize(75);
	_title->SetOriginAtMiddle();
	_title->SetZOrder(1);

	mainMenuCanvas->AddChild(_title);

	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);
	const Vector2f& _size = Vector2f(200.0f, 60.0f);

	//////////////////////////
	///		Play
	//////////////////////////

	const Vector2f& _playLocation = Vector2f(windowSize.x * 0.3f, windowSize.y * 0.8f);

	const FButtonAndLabelData& _playData = FButtonAndLabelData("PLAY", "PlayLabel", "PlayButton", "Widgets/Utility/ButtonsFrame", _playLocation,
		_size, _fontData, 25, 2);

	AButtonWidget* _playButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _playData);
	_playButton->BindOnClickAction([&]() { OpenMenu(startCanvas, mainMenuCanvas); });

	//////////////////////////
	///		LeaderBoard
	//////////////////////////

	const Vector2f& _leaderBoardLocation = Vector2f(windowSize.x * 0.4f, windowSize.y * 0.9);

	const FButtonAndLabelData& _leaderBoardData = FButtonAndLabelData("LEADERBOARD", "LeaderBoardLabel", "LeaderBoardButton",
		"Widgets/Utility/ButtonsFrame", _leaderBoardLocation, { 200.0f, 60.0f }, _fontData, 15, 2);

	AButtonWidget* _leaderBoardButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _leaderBoardData);
	_leaderBoardButton->BindOnClickAction([&]() { OpenMenu(leaderBoardCanvas, mainMenuCanvas); });

	//////////////////////////
	///		Credits
	//////////////////////////

	const Vector2f& _creditLocation = Vector2f(windowSize.x * 0.6f, windowSize.y * 0.9f);

	const FButtonAndLabelData& _creditData = FButtonAndLabelData("CREDITS", "CreditLabel", "CreditButton",
		"Widgets/Utility/ButtonsFrame", _creditLocation, { 150.0f, 60.0f }, _fontData, 15, 2);

	AButtonWidget* _creditButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _creditData);
	_creditButton->BindOnClickAction([&]() { OpenMenu(creditCanvas, mainMenuCanvas); });

	//////////////////////////
	///		Options
	//////////////////////////

	const Vector2f& _optionLocation = Vector2f(windowSize.x * 0.5f, windowSize.y * 0.8f);

	const FButtonAndLabelData& _optionData = FButtonAndLabelData("OPTIONS", "OptionLabel", "OptionButton",
		"Widgets/Utility/ButtonsFrame", _optionLocation, _size, _fontData, 25, 2);

	AButtonWidget* _optionButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _optionData);
	_optionButton->BindOnClickAction([&]() { OpenMenu(optionCanvas, mainMenuCanvas); });

	//////////////////////////
	///		Quit
	//////////////////////////

	const Vector2f& _quitLocation = Vector2f(windowSize.x * 0.7f, windowSize.y * 0.8f);

	const FButtonAndLabelData& _quitData = FButtonAndLabelData("QUIT", "QuitLabel", "QuitButton",
		"Widgets/Utility/ButtonsFrame", _quitLocation, _size, _fontData, 25, 2);

	AButtonWidget* _quitButton = InitButtonAndLabelData(_hud, mainMenuCanvas, _quitData);
	_quitButton->BindOnClickAction([&]() { window.close(); });

	mainMenuCanvas->SetVisibility(VisibilityType::Hidden);
}

void UMainMenuLevel::InitOptionMenu(HUD* _hud)
{
	if (!optionCanvas || !mainMenuCanvas) return;

	optionCanvas->AddChild(backgroundGIF);

	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);

	optionCanvas->SetSize(windowSize);

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("OPTIONS", "OptionTitleLabel", Screen);
	_title->SetCharacterSize(50);
	_title->SetFont(_fontData.first, _fontData.second);
	_title->SetOriginAtMiddle();
	_title->SetLocation(Vector2f(windowSize.x / 2.0f, windowSize.y * 0.1f));
	_title->SetZOrder(1);

	optionCanvas->AddChild(_title);


	ALabelWidget* _volumeLabel = _hud->SpawnWidget<ALabelWidget>("Main Volume", "OptionVolumeLabel", Screen);
	_volumeLabel->SetCharacterSize(25);
	_volumeLabel->SetFont(_fontData.first, _fontData.second);
	_volumeLabel->SetOriginAtMiddle();
	_volumeLabel->SetLocation(Vector2f(windowSize.x * 0.15f, windowSize.y * 0.3f));
	_volumeLabel->SetZOrder(1);

	optionCanvas->AddChild(_volumeLabel);

	sliderBar = _hud->SpawnWidget<SliderWidget>("OptionSliderLabel", Screen);
	sliderBar->SetMinValue(0.0f);
	sliderBar->SetMaxValue(10.0f);
	sliderBar->SetOriginAtMiddle();
	sliderBar->SetLocation(Vector2f(windowSize.x * 0.3f, windowSize.y * 0.3f));
	sliderBar->SetScale(Vector2f(100.0f, 1.0f));
	sliderBar->SetZOrder(2);
	sliderBar->GetButton()->BindOnReleaseAction([&]() { GetAudioManager().SetVolume(sliderBar->GetValue()); });
	sliderBar->SetValue(GetAudioManager().GetVolume());

	optionCanvas->AddChild(sliderBar);


	//////////////////////////
	///		Back
	//////////////////////////

	const Vector2f& _backLocation = Vector2f(windowSize.x * 0.9f, windowSize.y * 0.9f);

	const FButtonAndLabelData& _backData = FButtonAndLabelData("BACK", "BackOptionLabel", "BackOptionButton",
		"Widgets/Utility/ButtonsFrame", _backLocation, { 150.0f, 50.0f }, _fontData, 25, 2);

	AButtonWidget* _backButton = InitButtonAndLabelData(_hud, optionCanvas, _backData);
	_backButton->BindOnClickAction([&]() { OpenMenu(mainMenuCanvas, optionCanvas); });

	optionCanvas->SetVisibility(VisibilityType::Hidden);
}

void UMainMenuLevel::InitLeaderBoardMenu(HUD* _hud)
{
	if (!leaderBoardCanvas || !mainMenuCanvas) return;

	leaderBoardCanvas->AddChild(backgroundGIF);

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
	///		Players Data
	//////////////////////////

	const int _maxPlayersCounts = ULeaderBoardManager::GetInstance().GetMaxPosition();

	vector<ALabelWidget*> _playersLabel = vector<ALabelWidget*>();
	for (int _index = 0; _index < _maxPlayersCounts; _index++)
	{
		ALabelWidget* _playerLabel = _hud->SpawnWidget<ALabelWidget>("", "LeaderBoardPlayerData_" + to_string(_index + 1), Screen);
		_playerLabel->SetCharacterSize(15);
		_playerLabel->SetFont(_fontData.first, _fontData.second);
		_playerLabel->SetZOrder(1);

		leaderBoardCanvas->AddChild(_playerLabel);
		_playersLabel.push_back(_playerLabel);
	}
	ULeaderBoardManager::GetInstance().SetPlayersLabel(_playersLabel);


	//FPlayerData _playerData = FPlayerData("Francis", 1200);
	//ULeaderBoardManager::GetInstance().AddPlayerData(_playerData);
	//_playerData = FPlayerData("Stephanie", 400);
	//ULeaderBoardManager::GetInstance().AddPlayerData(_playerData);
	//_playerData = FPlayerData("Caca", 700);
	//ULeaderBoardManager::GetInstance().AddPlayerData(_playerData);

	//////////////////////////
	///		Back
	//////////////////////////

	const Vector2f& _backLocation = Vector2f(windowSize.x * 0.9f, windowSize.y * 0.9f);

	const FButtonAndLabelData& _backData = FButtonAndLabelData("BACK", "BackLeaderBoardLabel", "BackLeaderBoardButton",
		"Widgets/Utility/ButtonsFrame", _backLocation, { 150.0f, 50.0f }, _fontData, 25, 2);

	AButtonWidget* _backButton = InitButtonAndLabelData(_hud, leaderBoardCanvas, _backData);
	_backButton->BindOnClickAction([&]() { OpenMenu(mainMenuCanvas, leaderBoardCanvas); });

	leaderBoardCanvas->SetVisibility(VisibilityType::Hidden);
}

void UMainMenuLevel::InitStartMenu(HUD* _hud)
{
	if (!startCanvas || !mainMenuCanvas) return;

	startCanvas->AddChild(backgroundGIF);

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
	_controlsLabel->SetCharacterSize(30);
	_controlsLabel->SetFont(_fontData.first, _fontData.second);
	_controlsLabel->SetOriginAtMiddle();
	_controlsLabel->SetLocation(Vector2f(windowSize.x * 0.685f, windowSize.y * 0.3f));
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
	_controlsEchapLabel->SetCharacterSize(15);
	_controlsEchapLabel->SetFont(_fontData.first, _fontData.second);
	_controlsEchapLabel->SetOriginAtMiddle();
	_controlsEchapLabel->SetLocation(Vector2f(windowSize.x * 0.585f, windowSize.y * 0.5f));
	_controlsEchapLabel->SetZOrder(1);

	startCanvas->AddChild(_controlsEchapLabel);

	//////////////////////////
	///		Z 
	//////////////////////////

	AImageWidget* _controlsZImage = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 100.0f, 100.0f },
		"Widgets/MainMenu/Start/Keyboard_SpriteSheet", PNG, false, IntRect({ 32, 0 }, { 32, 32 })),
		"ControlsZImage", Screen);
	_controlsZImage->SetOriginAtMiddle();
	_controlsZImage->SetLocation(Vector2f(windowSize.x * 0.74f, windowSize.y * 0.4f));
	_controlsZImage->SetZOrder(1);

	startCanvas->AddChild(_controlsZImage);

	ALabelWidget* _controlsZLabel = _hud->SpawnWidget<ALabelWidget>("Accelerate", "ControlsZLabel", Screen);
	_controlsZLabel->SetCharacterSize(15);
	_controlsZLabel->SetFont(_fontData.first, _fontData.second);
	_controlsZLabel->SetOriginAtMiddle();
	_controlsZLabel->SetLocation(Vector2f(windowSize.x * 0.765f, windowSize.y * 0.5f));
	_controlsZLabel->SetZOrder(1);

	startCanvas->AddChild(_controlsZLabel);

	//////////////////////////
	///		Q 
	//////////////////////////

	AImageWidget* _controlsQImage = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 100.0f, 100.0f },
		"Widgets/MainMenu/Start/Keyboard_SpriteSheet", PNG, false, IntRect({ 64, 0 }, { 32, 32 })),
		"ControlsQImage", Screen);
	_controlsQImage->SetOriginAtMiddle();
	_controlsQImage->SetLocation(Vector2f(windowSize.x * 0.68f, windowSize.y * 0.55f));
	_controlsQImage->SetZOrder(1);

	startCanvas->AddChild(_controlsQImage);

	ALabelWidget* _controlsQLabel = _hud->SpawnWidget<ALabelWidget>("Rotate Left", "ControlsQLabel", Screen);
	_controlsQLabel->SetCharacterSize(15);
	_controlsQLabel->SetFont(_fontData.first, _fontData.second);
	_controlsQLabel->SetOriginAtMiddle();
	_controlsQLabel->SetLocation(Vector2f(windowSize.x * 0.7f, windowSize.y * 0.65f));
	_controlsQLabel->SetZOrder(1);

	startCanvas->AddChild(_controlsQLabel);

	//////////////////////////
	///		S
	//////////////////////////

	AImageWidget* _controlsSImage = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 100.0f, 100.0f },
		"Widgets/MainMenu/Start/Keyboard_SpriteSheet", PNG, false, IntRect({ 96, 0 }, { 32, 32 })),
		"ControlsSImage", Screen);
	_controlsSImage->SetOriginAtMiddle();
	_controlsSImage->SetLocation(Vector2f(windowSize.x * 0.59f, windowSize.y * 0.55f));
	_controlsSImage->SetZOrder(1);

	startCanvas->AddChild(_controlsSImage);

	ALabelWidget* _controlsSLabel = _hud->SpawnWidget<ALabelWidget>("OR", "ControlsSLabel", Screen);
	_controlsSLabel->SetCharacterSize(15);
	_controlsSLabel->SetFont(_fontData.first, _fontData.second);
	_controlsSLabel->SetOriginAtMiddle();
	_controlsSLabel->SetLocation(Vector2f(windowSize.x * 0.585f, windowSize.y * 0.6f));
	_controlsSLabel->SetZOrder(1);

	startCanvas->AddChild(_controlsSLabel);

	//////////////////////////
	///		D 
	//////////////////////////

	AImageWidget* _controlsDImage = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 100.0f, 100.0f },
		"Widgets/MainMenu/Start/Keyboard_SpriteSheet", PNG, false, IntRect({ 128, 0 }, { 32, 32 })),
		"ControlsDImage", Screen);
	_controlsDImage->SetOriginAtMiddle();
	_controlsDImage->SetLocation(Vector2f(windowSize.x * 0.8f, windowSize.y * 0.55f));
	_controlsDImage->SetZOrder(1);

	startCanvas->AddChild(_controlsDImage);

	ALabelWidget* _controlsDLabel = _hud->SpawnWidget<ALabelWidget>("Rotate Right", "ControlsDLabel", Screen);
	_controlsDLabel->SetCharacterSize(15);
	_controlsDLabel->SetFont(_fontData.first, _fontData.second);
	_controlsDLabel->SetOriginAtMiddle();
	_controlsDLabel->SetLocation(Vector2f(windowSize.x * 0.82f, windowSize.y * 0.65f));
	_controlsDLabel->SetZOrder(1);

	startCanvas->AddChild(_controlsDLabel);

	//////////////////////////
	///		Space Bar 
	//////////////////////////

	AImageWidget* _controlsSpaceBarImage = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({100.0f, 100.0f}, 
			"Widgets/MainMenu/Start/Keyboard_SpriteSheet", PNG, false, IntRect({160, 0},{32, 32})), 
			"ControlsSpaceBarImage", Screen);
	_controlsSpaceBarImage->SetOriginAtMiddle();
	_controlsSpaceBarImage->SetLocation(Vector2f(windowSize.x * 0.515f, windowSize.y * 0.55f));
	_controlsSpaceBarImage->SetZOrder(1);

	startCanvas->AddChild(_controlsSpaceBarImage);

	ALabelWidget* _controlsSpaceBarLabel = _hud->SpawnWidget<ALabelWidget>("Shoot", "ControlsSpacebarLabel", Screen);
	_controlsSpaceBarLabel->SetCharacterSize(15);
	_controlsSpaceBarLabel->SetFont(_fontData.first, _fontData.second);
	_controlsSpaceBarLabel->SetOriginAtMiddle();
	_controlsSpaceBarLabel->SetLocation(Vector2f(windowSize.x * 0.585f, windowSize.y * 0.65f));
	_controlsSpaceBarLabel->SetZOrder(1);

	startCanvas->AddChild(_controlsSpaceBarLabel);

	//////////////////////////
	///		Blur 
	//////////////////////////

	AImageWidget* _blur = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 750.0f, 700.0f },
		"Widgets/Utility/LightBlur", PNG, false),
		"PlayBlur", Screen);
	_blur->SetOriginAtMiddle();
	_blur->SetLocation(Vector2f(windowSize.x * 0.5f, windowSize.y * 0.2f));
	_blur->SetZOrder(0);

	startCanvas->AddChild(_blur);

	//////////////////////////
	///		Back
	//////////////////////////

	const Vector2f& _backLocation = Vector2f(windowSize.x * 0.9f, windowSize.y * 0.9f);

	const FButtonAndLabelData& _backData = FButtonAndLabelData("BACK", "BackStartLabel", "BackStartButton",
		"Widgets/Utility/ButtonsFrame", _backLocation, { 150.0f, 50.0f }, _fontData, 25, 2);

	AButtonWidget* _backButton = InitButtonAndLabelData(_hud, startCanvas, _backData);
	_backButton->BindOnClickAction([&]() { OpenMenu(mainMenuCanvas, startCanvas); });


	//////////////////////////
	///		Classic Mode
	//////////////////////////

	const Vector2f& _classicModeLocation = Vector2f(windowSize.x * 0.2f, windowSize.y * 0.35f);

	const FButtonAndLabelData& _classicModeData = FButtonAndLabelData("CLASSIC MODE", "ClassicModeStartLabel", "ClassicModeStartButton",
		"Widgets/Utility/ButtonsFrame", _classicModeLocation, { 500.0f, 150.0f }, _fontData, 40, 2);

	AButtonWidget* _classicModeButton = InitButtonAndLabelData(_hud, startCanvas, _classicModeData);
	_classicModeButton->BindOnClickAction([&]() 
	{ 
		float _tempVolume = GetAudioManager().GetVolume();
		OpenMenu(mainMenuCanvas, startCanvas); 
		M_LEVEL.SetLevel("ClassicModeLevel"); 
		backgroundTheme->Stop();
		if (UGameplayLevel* _level = Cast<UGameplayLevel>(M_LEVEL.GetCurrentLevel()))
		{
			_level->backgroundTheme->Play();
			_level->GetAudioManager().SetVolume(_tempVolume);
		}

	});


	//////////////////////////
	///		Chrono Mode
	//////////////////////////

	const Vector2f& _chronoModeLocation = Vector2f(windowSize.x * 0.2f, windowSize.y * 0.65f);

	const FButtonAndLabelData& _chronoModeData = FButtonAndLabelData("CHRONO MODE", "ChronoModeStartLabel", "ChronoModeStartButton",
		"Widgets/Utility/ButtonsFrame", _chronoModeLocation, { 500.0f, 150.0f }, _fontData, 40, 2);

	AButtonWidget* _chronoModeButton = InitButtonAndLabelData(_hud, startCanvas, _chronoModeData);
	_chronoModeButton->BindOnClickAction([&]() 
		{ 
			float _tempVolume = GetAudioManager().GetVolume();
			OpenMenu(mainMenuCanvas, startCanvas);
			M_LEVEL.SetLevel("ChronoModeLevel");
			backgroundTheme->Stop();
			if (UGameplayLevel* _level = Cast<UGameplayLevel>(M_LEVEL.GetCurrentLevel()))
			{
				_level->backgroundTheme->Play();
				_level->GetAudioManager().SetVolume(_tempVolume);
			}
		});



	startCanvas->SetVisibility(VisibilityType::Hidden);
}

void UMainMenuLevel::InitCreditMenu(HUD* _hud)
{
	if (!creditCanvas || !mainMenuCanvas) return;

	creditCanvas->AddChild(backgroundGIF);

	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);

	creditCanvas->SetSize(windowSize);

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("CREDITS", "CreditTitleLabel", Screen);
	_title->SetCharacterSize(50);
	_title->SetFont(_fontData.first, _fontData.second);
	_title->SetOriginAtMiddle();
	_title->SetLocation(Vector2f(windowSize.x / 2.0f, windowSize.y * 0.1f));
	_title->SetZOrder(1);

	creditCanvas->AddChild(_title);

	//////////////////////////
	///		Labels
	//////////////////////////

	ALabelWidget* _lead = _hud->SpawnWidget<ALabelWidget>("Sacha Gastinois", "CreditTitleLabel", Screen);
	_lead->SetCharacterSize(15);
	_lead->SetFont(_fontData.first, _fontData.second);
	_lead->SetOriginAtMiddle();
	_lead->SetLocation({ windowSize.x / 2.0f, windowSize.y / 2.0f});
	_lead->SetZOrder(1);

	creditCanvas->AddChild(_lead);


	//////////////////////////
	///		Back
	//////////////////////////

	const Vector2f& _backLocation = Vector2f(windowSize.x * 0.9f, windowSize.y * 0.9f);

	const FButtonAndLabelData& _backData = FButtonAndLabelData("BACK", "BackCreditLabel", "BackCreditButton",
		"Widgets/Utility/ButtonsFrame", _backLocation, { 150.0f, 50.0f }, _fontData, 25, 2);

	AButtonWidget* _backButton = InitButtonAndLabelData(_hud, creditCanvas, _backData);
	_backButton->BindOnClickAction([&]() { OpenMenu(mainMenuCanvas, creditCanvas); });

	creditCanvas->SetVisibility(VisibilityType::Hidden);
}

void UMainMenuLevel::InitBackgroundGIF(HUD* _hud)
{
	backgroundGIF = _hud->SpawnWidget<AGIFWidget>(RectangleShapeData(windowSize, "Widgets/MainMenu/BackgroundMainMenu"));
	backgroundGIF->SetZOrder(0);

	vector<SpriteData> _spriteMainMenuLoop;
	for (int _i = 0; _i < 12; _i++)
	{
		for (int _j = 0; _j < 8; _j++)
		{
			if (_i == 12 && _j < 8) continue;
			_spriteMainMenuLoop.push_back(SpriteData(Vector2i(_j * 914, _i * 570), Vector2i(914, 570)));
		}
	}
	Animation* _loopAnim = new Animation("MainMenu BackgroundLoop", backgroundGIF->GetComponent<UStaticMeshComponent>()->GetShape(), AnimationData(20.0f, _spriteMainMenuLoop, true, true));
	backgroundGIF->AddAnimation(_loopAnim);
}

void UMainMenuLevel::InitMainMenuTheme()
{
	backgroundTheme = SpawnSample<MusicSample>("MainMenuTheme");
	backgroundTheme->SetLoop(true);
	backgroundTheme->Play();
}


