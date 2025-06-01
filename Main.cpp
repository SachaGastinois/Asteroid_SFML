#include "Engine.h"
#include "LevelManager.h"
#include "MainMenuLevel.h"
#include "ClassicModeLevel.h"
#include "TESTLevel.h"

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

	TESTLevel* _aled = new TESTLevel("ALED");
	M_LEVEL.RegisterLevel(_aled->GetName(), _aled);

	M_LEVEL.SetLevel("ALED");

	Engine _engine;
	_engine.Start();

	return EXIT_SUCCESS;
}