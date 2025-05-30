#include "Engine.h"
#include "LevelManager.h"
#include "MainMenuLevel.h"
#include "ClassicModeLevel.h"

void InitConfig()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	Logger::Reset();
	system("cls");
}

int main()
{
	InitConfig();

	UMainMenuLevel* _mainMenuLevel = new UMainMenuLevel("MainMenuLevel");
	M_LEVEL.RegisterLevel(_mainMenuLevel->GetName(), _mainMenuLevel);

	UClassicModeLevel* _classicModeLevel = new UClassicModeLevel("ClassicModeLevel");
	M_LEVEL.RegisterLevel(_classicModeLevel->GetName(), _classicModeLevel);

	M_LEVEL.SetLevel("ClassicModeLevel");

	Engine _engine;
	_engine.Start();

	return EXIT_SUCCESS;
}