#include "TESTLevel.h"
#include "PlayerPawn.h"
#include "CircleActor.h"
#include "RectangleActor.h"
#include "CUSTOMGameMode.h"
#include "CanvasWidget.h"
#include "ImageWidget.h"
#include "Actor.h"
#include "CustomActor.h"
#include "TimerManager.h"

using namespace UI;

TESTLevel::TESTLevel(const string& _levelName) : Level(_levelName)
{

}

void TESTLevel::InitLevel()
{
	Super::InitLevel();

	GetCameraManager().GetCurrent()->SetLocation(GetWindowSize() / 2.0f);

	APlayerPawn* _player = SpawnActor<APlayerPawn>();
	_player->SetLocation(GetWindowSize() / 2.0f);

	CustomActor* _actor = SpawnActor<CustomActor>();
	_actor->SetLocation(GetWindowSize() / 1.5f);

	/*HUD* _hud = GetGameMode()->GetHUD();

	UI::CanvasWidget* canvas = _hud->SpawnWidget<UI::CanvasWidget>();
	canvas->SetSize(CAST(Vector2f, GetWindowSize()));

	ImageWidget* _image = _hud->SpawnWidget<ImageWidget>(CircleShapeData(50.0f));
	canvas->AddChild(_image);*/

	//GetGameMode()->GetHUD()->AddToViewport(canvas);

	new Timer(bind(&TESTLevel::KismetMousePos, this), seconds(0.5f), true, true);

}

void TESTLevel::Update(const float _deltaTime)
{
	Super::Update(_deltaTime);

	set<AActor*> _actors = GetActorManager().GetAllActors();

	for (AActor* _actor : _actors)
	{
		SetLocationIfOutOfBoundes(_actor);
	}
}

void TESTLevel::Load()
{
	Super::Load();

}

void TESTLevel::Unload()
{
	Super::Unload();

}

void TESTLevel::SetLocationIfOutOfBoundes(AActor* _actor)
{
	if (Cast<AWidget>(_actor)) return;

	const Vector2f& _windowSize = GetWindowSize();
	const Vector2f& _playerPosition = _actor->GetLocation();
	const Vector2f& _playerScale = _actor->GetScale();
	const Vector2f& _playerSize = Vector2f(_playerScale.x, _playerScale.y) / 2.0f;
	if ((_playerPosition.x + _playerSize.x) < 0.0f)
	{
		_actor->SetLocation({ _windowSize.x + _playerSize.x, _playerPosition.y });
	}
	else if ((_playerPosition.x - _playerSize.x) > _windowSize.x)
	{
		_actor->SetLocation({ 0.0f - _playerSize.x, _playerPosition.y });
	}
	if ((_playerPosition.y + _playerSize.y) < 0.0f)
	{
		_actor->SetLocation({ _playerPosition.x , _windowSize.y + _playerSize.y });
	}
	else if ((_playerPosition.y - _playerSize.y) > _windowSize.y)
	{
		_actor->SetLocation({ _playerPosition.x, 0.0f - _playerSize.y });
	}
}

void TESTLevel::KismetMousePos()
{
	Vector2i _mousePos = Mouse::getPosition();
	LOG(Display, to_string(_mousePos.x));
	LOG(Display, to_string(_mousePos.y));
}
