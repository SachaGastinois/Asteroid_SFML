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

using namespace UI;

UClassicModeLevel::UClassicModeLevel(const string& _levelName) : UGameplayLevel(_levelName)
{

}

void UClassicModeLevel::InitLevel()
{
	Super::InitLevel();

	
}
