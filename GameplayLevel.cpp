#include "GameplayLevel.h"
#include "PlayerPawn.h"
#include "UFO.h"
#include "Asteroid.h"
#include "LevelManager.h"
#include "MusicSample.h"
#include "LifeComponent.h"
#include "MainMenuLevel.h"
#include "LeaderBoardManager.h"
#include "ClassicModeLevel.h"
#include "Projectile.h"

UGameplayLevel::UGameplayLevel(const string& _levelName) : UUtilityLevel(_levelName)
{
	pauseCanvas = nullptr;
	gameplayCanvas = nullptr;
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

	GetAudioManager().SetVolume(GetAudioManager().GetVolume());

	HUD* _hud = GetGameMode()->GetHUD();

	pauseCanvas = _hud->SpawnWidget<UI::ACanvasWidget>("PauseCanvas");
	gameplayCanvas = _hud->SpawnWidget<UI::ACanvasWidget>("GameplayMenu");
	gameOverCanvas = _hud->SpawnWidget<UI::ACanvasWidget>("GameOverMenu");

	InitBackgroundGIF(_hud);

	InitGameOverCanvas(_hud);
	InitPauseMenu(_hud);
	InitGameplayCanvas(_hud);

	player = SpawnActor<APlayerPawn>();

	InitGameplayTheme();

	backgroundTheme->SetVolume(1.0f);
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

	UpdatePlayerLife();
}

void UGameplayLevel::InitPauseMenu(HUD* _hud)
{
	pauseCanvas->SetSize(CAST(Vector2f, windowSize));

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("PAUSE", "PauseLabel", Screen);
	_title->SetLocation(Vector2f(windowSize.x * 0.5f, windowSize.y * 0.3f));
	_title->SetFont("Daydream", TTF);
	_title->SetCharacterSize(75);
	_title->SetOriginAtMiddle();
	_title->SetZOrder(6);

	pauseCanvas->AddChild(_title);

	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);

	//////////////////////////
	///		Resume
	//////////////////////////

	const Vector2f& _pauseResumeLocation = Vector2f(windowSize.x * 0.5f, windowSize.y * 0.5f);

	const FButtonAndLabelData& _pauseResumeData = FButtonAndLabelData("RESUME", "PauseResumeLabel", "PauseResumeButton", "Widgets/Utility/ButtonsFrame",
		_pauseResumeLocation, { 400.0f, 60.0f }, _fontData, 25, 7);

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
		"Widgets/Utility/ButtonsFrame", _pauseMainMenuLocation, { 400.0f, 60.0f }, _fontData, 25, 7);

	AButtonWidget* _pauseMainMenuButton = InitButtonAndLabelData(_hud, pauseCanvas, _pauseMainMenuData);
	_pauseMainMenuButton->BindOnClickAction([&]() 
	{ 
		if (!isPause) return;
		backgroundTheme->Stop();
		
		GetGameMode()->GetHUD()->RemoveFromViewport(pauseCanvas);
		pauseCanvas->SetVisibility(VisibilityType::Hidden);

		isPause = false;
		M_LEVEL.SetLevel("MainMenuLevel"); 
		if (UMainMenuLevel* _level = Cast<UMainMenuLevel>(M_LEVEL.GetCurrentLevel()))
		{
			_level->backgroundTheme->Play();
		}
	});

	//////////////////////////
	///		Quit
	//////////////////////////

	const Vector2f& _pauseQuitLocation = Vector2f(windowSize.x * 0.5f, windowSize.y * 0.7f);

	const FButtonAndLabelData& _pauseQuitData = FButtonAndLabelData("QUIT TO DESKTOP", "PauseQuitLabel", "PauseQuitButton",
		"Widgets/Utility/ButtonsFrame", _pauseQuitLocation, { 400.0f, 60.0f }, _fontData, 25, 7);

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
	_lightBlur->SetZOrder(5);

	pauseCanvas->AddChild(_lightBlur);

	//////////////////////////
	///		Dark Blur 
	//////////////////////////

	AImageWidget* _darkBlur = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 1920.0f, 1080.0f },
		"Widgets/Utility/DarkBlur", PNG, false),
		"CreditDarkBlur", Screen);
	_darkBlur->SetOriginAtMiddle();
	_darkBlur->SetZOrder(4);

	pauseCanvas->AddChild(_darkBlur);

	pauseCanvas->SetVisibility(VisibilityType::Hidden);
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

	gameplayCanvas->SetVisibility(VisibilityType::Hidden);
}

void UGameplayLevel::InitGameOverCanvas(HUD* _hud)
{
	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);

	//////////////////////////
	///		Title
	//////////////////////////

	ALabelWidget* _gameOverLabel = _hud->SpawnWidget<ALabelWidget>("GAME OVER", "GameOverLabel", Screen);
	_gameOverLabel->SetLocation(Vector2f(windowSize.x * 0.5f, windowSize.y * 0.3f));
	_gameOverLabel->SetFont(_fontData.first, _fontData.second);
	_gameOverLabel->SetCharacterSize(75);
	_gameOverLabel->SetOriginAtMiddle();
	_gameOverLabel->SetZOrder(6);

	gameOverCanvas->AddChild(_gameOverLabel);

	//////////////////////////
	///		Return to Main Menu
	//////////////////////////

	const FButtonAndLabelData& _pauseQuitData = FButtonAndLabelData("RETURN TO MAIN MENU", "MainMenuLabel", "MainMenuButton",
		"Widgets/Utility/ButtonsFrame", { windowSize.x * 0.5f, windowSize.y * 0.8f }, {600.0f, 60.0f}, _fontData, 25, 7);

	AButtonWidget* _pauseQuitButton = InitButtonAndLabelData(_hud, gameOverCanvas, _pauseQuitData);
	_pauseQuitButton->BindOnClickAction([&]() 
	{ 
		backgroundTheme->Stop();

		GetGameMode()->GetHUD()->RemoveFromViewport(pauseCanvas);
		pauseCanvas->SetVisibility(VisibilityType::Hidden);

		isPause = false;

		if(Cast<UClassicModeLevel>(M_LEVEL.GetCurrentLevel()))
		{
			FPlayerData _playerData = FPlayerData(M_TIMER.GetCurrentRealTime(), currentScorePoint);
			ULeaderBoardManager::GetInstance().AddPlayerData(_playerData);
		}
		
		M_LEVEL.SetLevel("MainMenuLevel");
		if (UMainMenuLevel* _level = Cast<UMainMenuLevel>(M_LEVEL.GetCurrentLevel()))
		{
			_level->backgroundTheme->Play();
		}
	});

	//////////////////////////
	///		Dark Blur 
	//////////////////////////

	AImageWidget* _darkBlur = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 1920.0f, 1080.0f },
		"Widgets/Utility/DarkBlur", PNG, false),
		"UpgradeDarkBlur", Screen);
	_darkBlur->SetOriginAtMiddle();
	_darkBlur->SetZOrder(4);

	gameOverCanvas->AddChild(_darkBlur);

	gameOverCanvas->SetVisibility(VisibilityType::Hidden);
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

void UGameplayLevel::InitGameplayTheme()
{
	backgroundTheme = SpawnSample<MusicSample>("GameplayTheme");
	backgroundTheme->SetLoop(true);
	backgroundTheme->Play();
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

void UGameplayLevel::UpdatePlayerLife()
{
	set<AActor*> _actors = GetActorManager().GetAllActors();

	for (AActor* _actor : _actors)
	{
		if (APlayerPawn* _player = Cast<APlayerPawn>(_actor))
		{
			const int _currentLife = _player->GetLife()->GetLifeData().currentLife;
			const int _maxLife = _player->GetLife()->GetLifeData().maxLife;
			const int _lifeWidgetsCount = lifesWidgets.size();
			for (int _index = 0; _index < _maxLife; _index++)
			{
				if (_lifeWidgetsCount <= _index || !lifesWidgets[_index]) return;

				if (_index >= _currentLife)
				{
					lifesWidgets[_index]->SetActive(false);
					continue;
				}
				lifesWidgets[_index]->SetActive(true);
			}
			return;
		}
	}
}

void UGameplayLevel::Reset()
{
	GetAudioManager().SetVolume(GetAudioManager().GetVolume());

	currentScorePoint = 0;
	scorePointLabel->SetText(to_string(currentScorePoint));
	scorePointLabel->SetOriginAtMiddle();

	isPause = false;

	set<AActor*> _actors = GetActorManager().GetAllActors();

	for (AActor* _actor : _actors)
	{
		if (Cast<AUFO>(_actor) || Cast<AProjectile>(_actor) || Cast<AAsteroid>(_actor))
		{
			_actor->SetToDelete();
		}
	}

	GetGameMode()->GetHUD()->RemoveFromViewport(gameOverCanvas);
	gameOverCanvas->SetVisibility(VisibilityType::Hidden);
}
