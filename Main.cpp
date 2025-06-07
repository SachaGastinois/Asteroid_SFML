#include "Engine.h"
#include "LevelManager.h"
#include "MainMenuLevel.h"
#include "ClassicModeLevel.h"
#include "TESTLevel.h"
#include "ChronoModeLevel.h"

void InitConfig()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Logger::Reset();
	system("cls");
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	InitConfig();

	UMainMenuLevel* _mainMenuLevel = new UMainMenuLevel("MainMenuLevel");
	M_LEVEL.RegisterLevel(_mainMenuLevel->GetName(), _mainMenuLevel);

	UClassicModeLevel* _classicModeLevel = new UClassicModeLevel("ClassicModeLevel");
	M_LEVEL.RegisterLevel(_classicModeLevel->GetName(), _classicModeLevel);

	UChronoModeLevel* _chronoModeLevel = new UChronoModeLevel("ChronoModeLevel");
	M_LEVEL.RegisterLevel(_chronoModeLevel->GetName(), _chronoModeLevel);

	M_LEVEL.SetLevel("MainMenuLevel");

	Engine _engine;
	_engine.Start();

	return EXIT_SUCCESS;
}