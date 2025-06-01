#include "GameplayLevel.h"
#include "PlayerPawn.h"
#include "UFO.h"
#include "Asteroid.h"
#include "LevelManager.h"
#include "MusicSample.h"

UGameplayLevel::UGameplayLevel(const string& _levelName) : UUtilityLevel(_levelName)
{
	pauseCanvas = nullptr;
	gameplayCanvas = nullptr;
	ugradeCanvss = nullptr;
	backgroundGIF = nullptr;
	lifesWidgets = vector<UI::AImageWidget*>();
	scorePointLabel = nullptr;
	currentScorePoint = 0;
	isPause = false;
}

void UGameplayLevel::InitLevel()
{
	Super::InitLevel();

	windowSize = GetWindowSize();

	GetCameraManager().GetCurrent()->SetLocation(windowSize / 2.0f);

	HUD* _hud = GetGameMode()->GetHUD();

	pauseCanvas = _hud->SpawnWidget<UI::ACanvasWidget>("PauseCanvas");
	gameplayCanvas = _hud->SpawnWidget<UI::ACanvasWidget>("GameplayMenu");
	ugradeCanvss = _hud->SpawnWidget<UI::ACanvasWidget>("GameplayMenu");

	InitBackgroundGIF(_hud);

	InitPauseMenu(_hud);
	InitGameplayCanvas(_hud);
	InitUpgradeMenu(_hud);

	OpenMenu(gameplayCanvas, gameplayCanvas);

	APlayerPawn* _actor = SpawnActor<APlayerPawn>();
	_actor->SetLocation(GetWindowSize() / 2.0f);

	AAsteroid* _asteroid = SpawnActor<AAsteroid>(EAsteroidSize::AS_MEDIUM);
	_asteroid->SetLocation(GetWindowSize() * 0.3f);

	AUFO* _ufo = SpawnActor<AUFO>("Entity/UFO/UFOSpriteSheet_1");
	_ufo->SetLocation(GetWindowSize() * 0.4f);
}

void UGameplayLevel::Update(const float _deltaTime)
{
	Super::Update(_deltaTime);

	GetCameraManager().GetCurrent()->SetActive(true);

	set<AActor*> _actors = GetActorManager().GetAllActors();

	for (AActor* _actor : _actors)
	{
		SetLocationIfOutOfBoundes(_actor);
	}
}

void UGameplayLevel::InitPauseMenu(HUD* _hud)
{
	pauseCanvas->SetSize(CAST(Vector2f, windowSize));

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("PAUSE", "PauseLabel", Screen);
	_title->SetLocation(Vector2f(windowSize.x * 0.5f, windowSize.y * 0.3f));
	_title->SetFont("Daydream", TTF);
	_title->SetCharacterSize(75);
	_title->SetOriginAtMiddle();
	_title->SetZOrder(1);

	pauseCanvas->AddChild(_title);

	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);

	//////////////////////////
	///		Resume
	//////////////////////////

	const Vector2f& _pauseResumeLocation = Vector2f(windowSize.x * 0.5f, windowSize.y * 0.5f);

	const FButtonAndLabelData& _pauseResumeData = FButtonAndLabelData("RESUME", "PauseResumeLabel", "PauseResumeButton", "Widgets/Utility/ButtonsFrame",
		_pauseResumeLocation, { 400.0f, 60.0f }, _fontData, 25, 2);

	AButtonWidget* _pauseResumeButton = InitButtonAndLabelData(_hud, pauseCanvas, _pauseResumeData);
	_pauseResumeButton->BindOnClickAction([&]() 
	{
		if (!isPause) return;

		GetGameMode()->GetHUD()->RemoveFromViewport(pauseCanvas);
		pauseCanvas->SetVisibility(VisibilityType::Hidden);

		isPause = false;
	});

	//////////////////////////
	///		Main Menu
	//////////////////////////

	const Vector2f& _pauseMainMenuLocation = Vector2f(windowSize.x * 0.5f, windowSize.y * 0.6);

	const FButtonAndLabelData& _pauseMainMenuData = FButtonAndLabelData("RETURN TO MAIN", "PauseMainMenuLabel", "PauseMainMenuButton",
		"Widgets/Utility/ButtonsFrame", _pauseMainMenuLocation, { 400.0f, 60.0f }, _fontData, 25, 2);

	AButtonWidget* _pauseMainMenuButton = InitButtonAndLabelData(_hud, pauseCanvas, _pauseMainMenuData);
	_pauseMainMenuButton->BindOnClickAction([&]() 
	{ 
		if (!isPause) return;
		
		GetGameMode()->GetHUD()->RemoveFromViewport(pauseCanvas);
		pauseCanvas->SetVisibility(VisibilityType::Hidden);

		isPause = false;
		M_LEVEL.SetLevel("MainMenuLevel"); 
	});

	//////////////////////////
	///		Quit
	//////////////////////////

	const Vector2f& _pauseQuitLocation = Vector2f(windowSize.x * 0.5f, windowSize.y * 0.7f);

	const FButtonAndLabelData& _pauseQuitData = FButtonAndLabelData("QUIT TO DESKTOP", "PauseQuitLabel", "PauseQuitButton",
		"Widgets/Utility/ButtonsFrame", _pauseQuitLocation, { 400.0f, 60.0f }, _fontData, 25, 2);

	AButtonWidget* _pauseQuitButton = InitButtonAndLabelData(_hud, pauseCanvas, _pauseQuitData);
	_pauseQuitButton->BindOnClickAction([&]() { window.close(); });

	//////////////////////////
	///		Light Blur 
	//////////////////////////

	AImageWidget* _lightBlur = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 500.0f, 700.0f },
		"Widgets/Utility/LightBlur", PNG, false),
		"CreditLightBlur", Screen);
	_lightBlur->SetOriginAtMiddle();
	_lightBlur->SetLocation(Vector2f(windowSize.x * 0.37f, windowSize.y * 0.15f));
	_lightBlur->SetZOrder(0);

	pauseCanvas->AddChild(_lightBlur);

	//////////////////////////
	///		Dark Blur 
	//////////////////////////

	AImageWidget* _darkBlur = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 1000.0f, 1000.0f },
		"Widgets/Utility/DarkBlur", PNG, false),
		"CreditDarkBlur", Screen);
	_darkBlur->SetOriginAtMiddle();
	_darkBlur->SetZOrder(0);

	pauseCanvas->AddChild(_darkBlur);

}

void UGameplayLevel::InitGameplayCanvas(HUD* _hud)
{
	gameplayCanvas->AddChild(backgroundGIF);
	//gameplayCanvas->AddChild(movementEffectGIF);
	//gameplayCanvas->AddChild(movementEffectGIF1);
	//gameplayCanvas->AddChild(movementEffectGIF2);
	//gameplayCanvas->AddChild(movementEffectGIF3);

	//////////////////////////
	///		Lifes 
	//////////////////////////

	ALabelWidget* _lifesLabel = _hud->SpawnWidget<ALabelWidget>("P1 :", "LifesLabel", Screen);
	_lifesLabel->SetLocation(Vector2f(windowSize.x * 0.05f, windowSize.y * 0.05f));
	_lifesLabel->SetFont("Daydream", TTF);
	_lifesLabel->SetCharacterSize(30);
	_lifesLabel->SetOriginAtMiddle();
	_lifesLabel->SetZOrder(1);

	gameplayCanvas->AddChild(_lifesLabel);

	for (int _index = 0; _index < 5; _index++)
	{
		AImageWidget* _lifeWidget = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 100.0f, 100.0f },
			"Widgets/Gameplay/LifeImage", PNG, false),
			"LifeImage_" + _index, Screen);
		_lifeWidget->SetLocation(Vector2f(windowSize.x * 0.1f + windowSize.x * 0.05f * _index, windowSize.y * 0.01f));
		_lifeWidget->SetOriginAtMiddle();
		_lifeWidget->SetZOrder(1);

		gameplayCanvas->AddChild(_lifeWidget);

		lifesWidgets.push_back(_lifeWidget);
	}

	//////////////////////////
	///		Score
	//////////////////////////

	ALabelWidget* _scoreLabel = _hud->SpawnWidget<ALabelWidget>("Score : ", "ScoreLabel", Screen);
	_scoreLabel->SetLocation(Vector2f(windowSize.x * 0.85f, windowSize.y * 0.05f));
	_scoreLabel->SetFont("Daydream", TTF);
	_scoreLabel->SetCharacterSize(30);
	_scoreLabel->SetOriginAtMiddle();
	_scoreLabel->SetZOrder(1);

	gameplayCanvas->AddChild(_scoreLabel);

	scorePointLabel = _hud->SpawnWidget<ALabelWidget>(to_string(currentScorePoint), "ScorePointLabel", Screen);
	scorePointLabel->SetLocation(Vector2f(windowSize.x * 0.95f, windowSize.y * 0.05f));
	scorePointLabel->SetFont("Daydream", TTF);
	scorePointLabel->SetCharacterSize(30);
	scorePointLabel->SetOriginAtMiddle();
	scorePointLabel->SetZOrder(1);

	gameplayCanvas->AddChild(scorePointLabel);


}

void UGameplayLevel::InitUpgradeMenu(HUD* _hud)
{

}

void UGameplayLevel::InitBackgroundGIF(HUD* _hud)
{
	backgroundGIF = _hud->SpawnWidget<AGIFWidget>(RectangleShapeData(windowSize, "Widgets/Gameplay/BackgroundGameplay1"));
	backgroundGIF->SetZOrder(0);

	vector<SpriteData> _spriteMainMenuLoop;
	for (int _i = 0; _i < 27; _i++)
	{
		for (int _j = 0; _j < 5; _j++)
		{
			if (_i == 5 && _j < 27) continue;
			_spriteMainMenuLoop.push_back(SpriteData(Vector2i(_j * 750, _i * 425), Vector2i(750, 425)));
		}
	}
	Animation* _loopAnim = new Animation("MainMenu BackgroundLoop", backgroundGIF->GetComponent<UStaticMeshComponent>()->GetShape(), AnimationData(10.0f, _spriteMainMenuLoop, true, true));
	backgroundGIF->AddAnimation(_loopAnim);


	//movementEffectGIF = _hud->SpawnWidget<AGIFWidget>(RectangleShapeData(windowSize, "Widgets/Gameplay/BackgroundGameplay"));
	//movementEffectGIF->SetZOrder(1);

	//vector<SpriteData> _spriteMovementLoop;
	//for (int _i = 0; _i < 4; _i++)
	//{
	//	for (int _j = 0; _j < 10; _j++)
	//	{
	//		if (_i == 10 && _j < 4) continue;
	//		_spriteMovementLoop.push_back(SpriteData(Vector2i(_j * 200, _i * 224), Vector2i(200, 224)));
	//	}
	//}
	//Animation* _movementLoopAnim = new Animation("MovementEffectLoop", movementEffectGIF->GetComponent<UStaticMeshComponent>()->GetShape(), AnimationData(5.0f, _spriteMovementLoop, true, true));
	//movementEffectGIF->AddAnimation(_movementLoopAnim);

	/*movementEffectGIF1 = _hud->SpawnWidget<AGIFWidget>(RectangleShapeData(windowSize * 0.5f, "Widgets/Gameplay/BackgroundGameplay"));
	movementEffectGIF1->SetZOrder(1);
	movementEffectGIF1->SetLocation(Vector2f(0.0f, windowSize.y / 2.0f));
	Animation* _movementLoopAnim1 = new Animation("MovementEffectLoop1", movementEffectGIF1->GetComponent<UStaticMeshComponent>()->GetShape(), AnimationData(5.0f, _spriteMovementLoop, true, true));
	movementEffectGIF1->AddAnimation(_movementLoopAnim1);

	movementEffectGIF2 = _hud->SpawnWidget<AGIFWidget>(RectangleShapeData(windowSize * 0.5f, "Widgets/Gameplay/BackgroundGameplay"));
	movementEffectGIF2->SetZOrder(1);
	movementEffectGIF2->SetLocation(Vector2f(windowSize.y / 2.0f, 0.0f));
	Animation* _movementLoopAnim2 = new Animation("MovementEffectLoop2", movementEffectGIF2->GetComponent<UStaticMeshComponent>()->GetShape(), AnimationData(5.0f, _spriteMovementLoop, true, true));
	movementEffectGIF2->AddAnimation(_movementLoopAnim2);

	movementEffectGIF3 = _hud->SpawnWidget<AGIFWidget>(RectangleShapeData(windowSize * 0.5f, "Widgets/Gameplay/BackgroundGameplay"));
	movementEffectGIF3->SetZOrder(1);
	movementEffectGIF3->SetLocation(Vector2f(windowSize.y / 2.0f, windowSize.y / 2.0f));
	Animation* _movementLoopAnim3 = new Animation("MovementEffectLoop3", movementEffectGIF3->GetComponent<UStaticMeshComponent>()->GetShape(), AnimationData(5.0f, _spriteMovementLoop, true, true));
	movementEffectGIF3->AddAnimation(_movementLoopAnim3);*/

}

void UGameplayLevel::InitMainMenuTheme()
{
	MusicSample* _sample = SpawnActor<MusicSample>("MainMenuTheme.mp3");
	_sample->SetLoop(true);
	GetAudioManager().RegisterSample(_sample);
	//GetAudioManager().PlaySample(_sample);
}

void UGameplayLevel::SetLocationIfOutOfBoundes(AActor* _actor)
{
	if (Cast<AWidget>(_actor)) return;

	const Vector2f& _playerPosition = _actor->GetLocation();
	const Vector2f& _playerScale = _actor->GetScale();
	const Vector2f& _playerSize = Vector2f(_playerScale.x, _playerScale.y) / 2.0f;
	if ((_playerPosition.x + _playerSize.x) < 0.0f)
	{
		_actor->SetLocation({ windowSize.x + _playerSize.x, _playerPosition.y });
	}
	else if ((_playerPosition.x - _playerSize.x) > windowSize.x)
	{
		_actor->SetLocation({ 0.0f - _playerSize.x, _playerPosition.y });
	}
	if ((_playerPosition.y + _playerSize.y) < 0.0f)
	{
		_actor->SetLocation({ _playerPosition.x , windowSize.y + _playerSize.y });
	}
	else if ((_playerPosition.y - _playerSize.y) > windowSize.y)
	{
		_actor->SetLocation({ _playerPosition.x, 0.0f - _playerSize.y });
	}
}

