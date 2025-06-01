#include "ChronoModeLevel.h"
#include "PlayerPawn.h"
#include "CircleActor.h"
#include "CUSTOMGameMode.h"
#include "CanvasWidget.h"
#include "ImageWidget.h"
#include "LabelWidget.h"
#include "ButtonWidget.h"
#include "LevelManager.h"
#include "MainMenuLevel.h"
#include "LeaderBoardManager.h"
#include "MusicSample.h"
#include "StaticMeshComponent.h"
#include "Asteroid.h"
#include "UFO.h"
#include "ShootComponent.h"
#include "Projectile.h"

UChronoModeLevel::UChronoModeLevel(const string& _levelName) : UGameplayLevel(_levelName)
{
	currentTime = 0.0f;
	baseTime = 150.0f;
	currentSpawnTime = 15.0f;
	spawnTime = 15.0f;
	isTimerRunning = true;
}

void UChronoModeLevel::InitLevel()
{
	Super::InitLevel();

	currentTime = baseTime;
	isTimerRunning = true;

	HUD* _hud = GetGameMode()->GetHUD();

	timesUpCanvas = _hud->SpawnWidget<UI::ACanvasWidget>("UpgradeMenu");

	InitTimesUpCanvas(_hud);

	player->GetShoot()->SetUpgradeStage(2);
	player->GetLife()->AddLife(2);

	player->SetCanShoot(true);

	player->SetActive(true);

	player->SetLocation(GetWindowSize() / 2.0f);

	OpenMenu(gameplayCanvas, gameplayCanvas);
}

void UChronoModeLevel::Update(const float _deltaTime)
{
	Super::Update(_deltaTime);

	if (isTimerRunning)
	{
		UpdateTimer(_deltaTime);
		timerLabel->SetText(TimerToString());
		UpdateSpawnTimer(_deltaTime);
	}
}

void UChronoModeLevel::InitGameplayCanvas(HUD* _hud)
{
	Super::InitGameplayCanvas(_hud);

	//////////////////////////
	///		Title
	//////////////////////////

	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);

	timerLabel = _hud->SpawnWidget<ALabelWidget>(TimerToString(), "TimesUpLabel", Screen);
	timerLabel->SetLocation(Vector2f(windowSize.x * 0.5f, windowSize.y * 0.1f));
	timerLabel->SetFont(_fontData.first, _fontData.second);
	timerLabel->SetCharacterSize(60);
	timerLabel->SetOriginAtMiddle();
	timerLabel->SetZOrder(6);

	gameplayCanvas->AddChild(timerLabel);

}

void UChronoModeLevel::InitTimesUpCanvas(HUD* _hud)
{
	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);

	//////////////////////////
	///		Title
	//////////////////////////

	ALabelWidget* _gameOverLabel = _hud->SpawnWidget<ALabelWidget>("TIME'S UP", "TimesUpLabel", Screen);
	_gameOverLabel->SetLocation(Vector2f(windowSize.x * 0.5f, windowSize.y * 0.3f));
	_gameOverLabel->SetFont(_fontData.first, _fontData.second);
	_gameOverLabel->SetCharacterSize(75);
	_gameOverLabel->SetOriginAtMiddle();
	_gameOverLabel->SetZOrder(6);

	timesUpCanvas->AddChild(_gameOverLabel);

	//////////////////////////
	///		Return to Main Menu
	//////////////////////////

	const FButtonAndLabelData& _pauseQuitData = FButtonAndLabelData("RETURN TO MAIN MENU", "MainMenuTimesUpLabel", "TimesUpButton",
		"Widgets/Utility/ButtonsFrame", { windowSize.x * 0.5f, windowSize.y * 0.8f }, { 600.0f, 60.0f }, _fontData, 25, 7);

	AButtonWidget* _pauseQuitButton = InitButtonAndLabelData(_hud, timesUpCanvas, _pauseQuitData);
	_pauseQuitButton->BindOnClickAction([&]()
		{
			backgroundTheme->Stop();

			GetGameMode()->GetHUD()->RemoveFromViewport(pauseCanvas);
			pauseCanvas->SetVisibility(VisibilityType::Hidden);

			isPause = false;
			M_LEVEL.SetLevel("MainMenuLevel");
			backgroundTheme->Stop();
			if (UMainMenuLevel* _level = Cast<UMainMenuLevel>(M_LEVEL.GetCurrentLevel()))
			{
				_level->backgroundTheme->Play();

				FPlayerData _playerData = FPlayerData(M_TIMER.GetCurrentRealTime(), currentScorePoint);
				ULeaderBoardManager::GetInstance().AddPlayerData(_playerData);
			}
		});

	//////////////////////////
	///		Dark Blur 
	//////////////////////////

	AImageWidget* _darkBlur = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 1920.0f, 1080.0f },
		"Widgets/Utility/DarkBlur", PNG, false),
		"TimesUpDarkBlur", Screen);
	_darkBlur->SetOriginAtMiddle();
	_darkBlur->SetZOrder(4);

	timesUpCanvas->AddChild(_darkBlur);

	timesUpCanvas->SetVisibility(VisibilityType::Hidden);
}

string UChronoModeLevel::TimerToString()
{
	const int _minutes = currentTime / 60;
	const int _seconds = fmod(currentTime, 60);
	const string& _finalText = to_string(_minutes) + ":" + to_string(_seconds);

	return _finalText;
}

void UChronoModeLevel::UpdateTimer(const float _deltaTime)
{
	currentTime -= _deltaTime;

	if (currentTime <= 0.0f)
	{
		isTimerRunning = false;
		OnTimerFinished();
	}
}

void UChronoModeLevel::UpdateSpawnTimer(const float _deltaTime)
{
	currentSpawnTime += _deltaTime;

	if (currentSpawnTime >= spawnTime)
	{
		currentSpawnTime = 0.0f;
		SpawnAsteroid();
		SpawnUFO();
	}
}

void UChronoModeLevel::OnTimerFinished()
{
	LOG(Display, "Timer Is Finished");

	isPause = true;

	set<AActor*> _actors = GetActorManager().GetAllActors();

	for (AActor* _actor : _actors)
	{
		if (AProjectile* _projectile = Cast<AProjectile>(_actor))
		{
			_projectile->SetZOrder(0);
		}
	}

	player->SetCanShoot(false);
	player->SetActive(false);

	GetGameMode()->GetHUD()->AddToViewport(timesUpCanvas);
	timesUpCanvas->SetVisibility(VisibilityType::Visible);

}

void UChronoModeLevel::SpawnAsteroid()
{
	const int _asteroidToSpawn = 6;
	for (int _index = 0; _index < _asteroidToSpawn; _index++)
	{
		AAsteroid* _asteroid = SpawnActor<AAsteroid>(EAsteroidSize::AS_BIG);
		_asteroid->SetLocation({ 0.0f, GetRandomNumberInRange(0.0f, windowSize.y) });
	}
}

void UChronoModeLevel::SpawnUFO()
{
	const int _ufoToSpawn = 2;
	for (int _index = 0; _index < _ufoToSpawn; _index++)
	{
		const string& _num = to_string(GetRandomNumberInRange(1, 3));
		AUFO* _ufo = SpawnActor<AUFO>("Entity/UFO/UFOSpriteSheet_" + _num);
		_ufo->SetLocation({ 0.0f, GetRandomNumberInRange(0.0f, windowSize.y) });
	}
}

void UChronoModeLevel::Reset()
{
	Super::Reset();

	currentTime = baseTime;
	currentSpawnTime = 15.0f;
	spawnTime = 15.0f;
	isTimerRunning = true;

	player->GetShoot()->SetUpgradeStage(2);
	player->GetLife()->AddLife(2);

	player->SetCanShoot(true);

	player->SetActive(true);

	player->SetLocation(GetWindowSize() / 2.0f);

	GetGameMode()->GetHUD()->RemoveFromViewport(timesUpCanvas);
	timesUpCanvas->SetVisibility(VisibilityType::Hidden);
}
