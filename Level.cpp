#include "Level.h"
#include "LevelManager.h"
#include "ActorManager.h"
#include "CameraManager.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "GameMode.h"
#include "MainMenuLevel.h"
#include "GameplayLevel.h"

Level::Level(const string& _name)
{
	isLoaded = false;
	name = _name;
	actorManager = ActorManager();
	cameraManager = Camera::UCameraManager();
	collisionManager = CollisionManager();
	audioManager = AudioManager();
	gameMode = nullptr;

	window.create(VideoMode({ 1920, 1080 }), GetName(), Style::None, State::Windowed);
	window.setVisible(false);
	M_LEVEL.RegisterLevel(_name, this);
}


void Level::UpdateWindow()
{
	window.clear();
	cameraManager.Render(window, GetGameMode()->IsSplitScreen());
	window.display();
}

void Level::InitLevel()
{
	ACameraActor* _camera = SpawnActor<ACameraActor>("DefaultCamera");
	cameraManager.Register(_camera->GetCamera());
}

void Level::Update(const float _deltaTime)
{
	UpdateWindow();
	actorManager.Update(_deltaTime);

	if (!window.isOpen())
	{
		M_LEVEL.SetLevel(nullptr);
	}
}

void Level::Load()
{
	if (!isLoaded)
	{
		InitLevel();
		isLoaded = true;
	}

	set<AActor*> _actors = GetActorManager().GetAllActors();

	for (AActor* _actor : _actors)
	{
		_actor->SetActive(true);
	}

	if (UGameplayLevel* _level = Cast<UGameplayLevel>(this))
	{
		_level->Reset();
	}

	window.setVisible(true);
	// Changement BeginPlay Individuelle à chaque Création d'Actor
	//actorManager.BeginPlay();
}

void Level::Unload()
{
	set<AActor*> _actors = GetActorManager().GetAllActors();

	for (AActor* _actor : _actors)
	{
		_actor->SetActive(false);
	}
	window.setVisible(false);
	window.clear();
	actorManager.BeginDestroy();
}