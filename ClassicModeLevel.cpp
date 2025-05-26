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

using namespace UI;

UClassicModeLevel::UClassicModeLevel(const string& _levelName) : UUtilityLevel(_levelName)
{

}

void UClassicModeLevel::InitLevel()
{
	Super::InitLevel();

	windowSize = GetWindowSize();

	HUD* _hud = GetGameMode()->GetHUD();

	pauseMenu = _hud->SpawnWidget<UI::ACanvasWidget>("PauseMenu");

	InitPauseMenu(_hud);

	FPlayerData _playerData = FPlayerData("Albert", 99989);
	ULeaderBoardManager::GetInstance().AddPlayerData(_playerData);

	OpenMenu(pauseMenu, pauseMenu);
}

void UClassicModeLevel::InitPauseMenu(HUD* _hud)
{
	pauseMenu->SetSize(CAST(Vector2f, windowSize));

	ALabelWidget* _title = _hud->SpawnWidget<ALabelWidget>("PAUSE", "PauseLabel", Screen);
	_title->SetLocation(Vector2f(windowSize.x * 0.5f, windowSize.y * 0.3f));
	_title->SetFont("Daydream", TTF);
	_title->SetCharacterSize(75);
	_title->SetOriginAtMiddle();
	_title->SetZOrder(1);

	pauseMenu->AddChild(_title);

	const pair<string, FontExtensionType>& _fontData = pair<string, FontExtensionType>("Daydream", TTF);

	//////////////////////////
	///		Resume
	//////////////////////////

	const Vector2f& _pauseResumeLocation = Vector2f(windowSize.x * 0.5f, windowSize.y * 0.5f);

	const FButtonAndLabelData& _pauseResumeData = FButtonAndLabelData("RESUME", "PauseResumeLabel", "PauseResumeButton", "",
		_pauseResumeLocation, { 200.0f, 50.0f }, _fontData, 25, 2);

	ButtonWidget* _pauseResumeButton = InitButtonAndLabelData(_hud, pauseMenu, _pauseResumeData);
	_pauseResumeButton->BindOnClickAction([&]() { LOG(Display, "Resume"); });

	//////////////////////////
	///		Main Menu
	//////////////////////////

	const Vector2f& _pauseMainMenuLocation = Vector2f(windowSize.x * 0.5f, windowSize.y * 0.6);

	const FButtonAndLabelData& _pauseMainMenuData = FButtonAndLabelData("RETURN TO MAIN", "PauseMainMenuLabel", "PauseMainMenuButton",
		"", _pauseMainMenuLocation, { 350.0f, 50.0f }, _fontData, 25, 2);

	ButtonWidget* _pauseMainMenuButton = InitButtonAndLabelData(_hud, pauseMenu, _pauseMainMenuData);
	_pauseMainMenuButton->BindOnClickAction([&]() { M_LEVEL.SetLevel("MainMenuLevel"); });

	//////////////////////////
	///		Quit
	//////////////////////////

	const Vector2f& _pauseQuitLocation = Vector2f(windowSize.x * 0.5f, windowSize.y * 0.7f);

	const FButtonAndLabelData& _pauseQuitData = FButtonAndLabelData("QUIT TO DESKTOP", "PauseQuitLabel", "PauseQuitButton",
		"", _pauseQuitLocation, { 350.0f, 50.0f }, _fontData, 25, 2);

	ButtonWidget* _pauseQuitButton = InitButtonAndLabelData(_hud, pauseMenu, _pauseQuitData);
	_pauseQuitButton->BindOnClickAction([&]() { window.close(); });
}
