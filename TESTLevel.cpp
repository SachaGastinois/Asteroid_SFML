#include "TESTLevel.h"
#include "PlayerPawn.h"

TESTLevel::TESTLevel(const string& _levelName) : Level(_levelName)
{
}

void TESTLevel::InitLevel()
{
	Super::InitLevel();

	AActor* _actor = SpawnActor<APlayerPawn>();


	_actor->SetPosition(GetWindowSize() / 2.0f);

	GetGameMode()->GetPlayerController();
}
