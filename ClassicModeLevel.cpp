#include "ClassicModeLevel.h"
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

using namespace UI;

UClassicModeLevel::UClassicModeLevel(const string& _levelName) : UGameplayLevel(_levelName)
{
	difficulty = 1.0f;
	asteroidBaseCount = 4;
	ufoBaseCount = 1;

	entityLeft = 0;
	isWaveOnGoing = false;

	upgradeCanvas = nullptr;
}

void UClassicModeLevel::InitLevel()
{
	Super::InitLevel();

	HUD* _hud = GetGameMode()->GetHUD();

	upgradeCanvas = _hud->SpawnWidget<UI::ACanvasWidget>("UpgradeMenu");

	InitUpgradeMenu(_hud);

	OpenMenu(gameplayCanvas, gameplayCanvas);

	StartWave();
}

void UClassicModeLevel::Update(const float _deltaTime)
{
	Super::Update(_deltaTime);

	if (isWaveOnGoing)
	{
		if (entityLeft <= 0)
		{
			OnWaveOver();
			isWaveOnGoing = false;
			entityLeft = 0;
		}
	}
}

void UClassicModeLevel::InitUpgradeMenu(HUD* _hud)
{
	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);

	//////////////////////////
	///		Title
	//////////////////////////

	ALabelWidget* _upgradeLabel = _hud->SpawnWidget<ALabelWidget>("CHOOSE ONE UPGRADE", "UpgradeLabel", Screen);
	_upgradeLabel->SetLocation(Vector2f(windowSize.x * 0.5f, windowSize.y * 0.2f));
	_upgradeLabel->SetFont("Daydream", TTF);
	_upgradeLabel->SetCharacterSize(75);
	_upgradeLabel->SetOriginAtMiddle();
	_upgradeLabel->SetZOrder(6);

	upgradeCanvas->AddChild(_upgradeLabel);

	//////////////////////////
	///		Shoot Upgrade
	//////////////////////////

	ALabelWidget* _shootUpgradeLabel = _hud->SpawnWidget<ALabelWidget>("Shoot++", "ShootUpgradeLabel", Screen);
	_shootUpgradeLabel->SetLocation({ windowSize.x * 0.73f, windowSize.y * 0.68f });
	_shootUpgradeLabel->SetFont(_fontData.first, _fontData.second);
	_shootUpgradeLabel->SetCharacterSize(50);
	_shootUpgradeLabel->SetOriginAtMiddle();
	_shootUpgradeLabel->SetZOrder(6);

	upgradeCanvas->AddChild(_shootUpgradeLabel);

	AImageWidget* _shootUpgradeImage = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 200.0f,200.0f }, "Widgets/Gameplay/ShootImage"),
		"ShootUpgradeImage", Screen);
	_shootUpgradeImage->SetLocation({ windowSize.x * 0.68f, windowSize.y * 0.4f });
	_shootUpgradeImage->SetOriginAtMiddle();
	_shootUpgradeImage->SetZOrder(6);

	upgradeCanvas->AddChild(_shootUpgradeImage);

	AButtonWidget* _shootUpgradeButton = _hud->SpawnWidget<AButtonWidget>(RectangleShapeData({ 500.0f, 500.0f },
		"Widgets/Utility/LightBlur"), "ShootUpgradeButton", Screen);
	_shootUpgradeButton->SetLocation({ windowSize.x * 0.6f, windowSize.y * 0.3f });
	_shootUpgradeButton->SetOriginAtMiddle();
	_shootUpgradeButton->SetZOrder(5);
	_shootUpgradeButton->BindOnClickAction([&]()
	{
		player->GetShoot()->SetUpgradeStage(player->GetShoot()->GetUpgradeStage() + 1);

		GetGameMode()->GetHUD()->RemoveFromViewport(upgradeCanvas);
		upgradeCanvas->SetVisibility(VisibilityType::Hidden);

		StartWave();
	});

	upgradeCanvas->AddChild(_shootUpgradeButton);

	//////////////////////////
	///		Life Upgrade
	//////////////////////////

	ALabelWidget* _lifeUpgradeLabel = _hud->SpawnWidget<ALabelWidget>("Life++", "LifeUpgradeLabel", Screen);
	_lifeUpgradeLabel->SetLocation({ windowSize.x * 0.26f, windowSize.y * 0.68f });
	_lifeUpgradeLabel->SetFont(_fontData.first, _fontData.second);
	_lifeUpgradeLabel->SetCharacterSize(50);
	_lifeUpgradeLabel->SetOriginAtMiddle();
	_lifeUpgradeLabel->SetZOrder(6);

	upgradeCanvas->AddChild(_lifeUpgradeLabel);

	AImageWidget* _lifeUpgradeImage = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 200.0f,200.0f }, "Widgets/Gameplay/LifeImage"),
		"LifeUpgradeImage", Screen);
	_lifeUpgradeImage->SetLocation({ windowSize.x * 0.21f, windowSize.y * 0.4f });
	_lifeUpgradeImage->SetOriginAtMiddle();
	_lifeUpgradeImage->SetZOrder(6);

	upgradeCanvas->AddChild(_lifeUpgradeImage);

	AButtonWidget* _lifeUpgradeButton = _hud->SpawnWidget<AButtonWidget>(RectangleShapeData({ 500.0f, 500.0f },
		"Widgets/Utility/LightBlur"), "LifeUpgradeButton", Screen);
	_lifeUpgradeButton->SetLocation({ windowSize.x * 0.13f, windowSize.y * 0.3f });
	_lifeUpgradeButton->SetOriginAtMiddle();
	_lifeUpgradeButton->SetZOrder(5);
	_lifeUpgradeButton->BindOnClickAction([&]()
	{
		player->GetLife()->AddLife(1);

		GetGameMode()->GetHUD()->RemoveFromViewport(upgradeCanvas);
		upgradeCanvas->SetVisibility(VisibilityType::Hidden);

		StartWave();
	});

	upgradeCanvas->AddChild(_lifeUpgradeButton);

	//////////////////////////
	///		Dark Blur 
	//////////////////////////

	AImageWidget* _darkBlur = _hud->SpawnWidget<AImageWidget>(RectangleShapeData({ 1920.0f, 1080.0f },
		"Widgets/Utility/DarkBlur", PNG, false),
		"UpgradeDarkBlur", Screen);
	_darkBlur->SetOriginAtMiddle();
	_darkBlur->SetZOrder(4);

	upgradeCanvas->AddChild(_darkBlur);

	upgradeCanvas->SetVisibility(VisibilityType::Hidden);
}

void UClassicModeLevel::StartWave()
{
	player->SetCanShoot(true);

	player->SetActive(true);

	isWaveOnGoing = true;

	player->SetLocation(GetWindowSize() / 2.0f);

	SpawnAsteroid();
	SpawnUFO();
}

void UClassicModeLevel::OnWaveOver()
{
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

	GetGameMode()->GetHUD()->AddToViewport(upgradeCanvas);
	upgradeCanvas->SetVisibility(VisibilityType::Visible);

	difficulty += 0.5f;
}

void UClassicModeLevel::SpawnAsteroid()
{
	const int _asteroidToSpawn = asteroidBaseCount * difficulty;
	for (int _index = 0; _index < _asteroidToSpawn; _index++)
	{
		AAsteroid* _asteroid = SpawnActor<AAsteroid>(EAsteroidSize::AS_BIG);
		_asteroid->SetLocation({ 0.0f, GetRandomNumberInRange(0.0f, windowSize.y) }); 
		entityLeft += 7;
	}
}

void UClassicModeLevel::SpawnUFO()
{
	const int _ufoToSpawn = ufoBaseCount * difficulty;
	for (int _index = 0; _index < _ufoToSpawn; _index++)
	{
		const string& _num = to_string(GetRandomNumberInRange(1, 3));
		AUFO* _ufo = SpawnActor<AUFO>("Entity/UFO/UFOSpriteSheet_" + _num);
		_ufo->SetLocation({ 0.0f, GetRandomNumberInRange(0.0f, windowSize.y) });
		entityLeft++;
	}
}

void UClassicModeLevel::Reset()
{
	Super::Reset();

	difficulty = 1.0f;

	entityLeft = 0;
	isWaveOnGoing = false;

	player->GetShoot()->SetUpgradeStage(0);
	player->GetLife()->SetCurrentLife(3);

	player->SetCanShoot(true);

	player->SetActive(true);

	player->SetLocation(GetWindowSize() / 2.0f);

	StartWave();
}
