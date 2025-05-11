#include "TESTLevel.h"
#include "PlayerPawn.h"
#include "CircleActor.h"
#include "RectangleActor.h"
#include "CUSTOMGameMode.h"
#include "CanvasWidget.h"
#include "ImageWidget.h"
#include "Actor.h"

using namespace UI;

TESTLevel::TESTLevel(const string& _levelName) : Level(_levelName)
{

}

void TESTLevel::InitLevel()
{
	Super::InitLevel();

	GetCameraManager().GetCurrent()->SetLocation(GetWindowSize() / 2.0f);

	APlayerPawn* _actor = SpawnActor<APlayerPawn>();
	_actor->SetLocation(GetWindowSize() / 2.0f);

	/*HUD* _hud = GetGameMode()->GetHUD();

	UI::CanvasWidget* canvas = _hud->SpawnWidget<UI::CanvasWidget>();
	canvas->SetSize(CAST(Vector2f, GetWindowSize()));

	ImageWidget* _image = _hud->SpawnWidget<ImageWidget>(CircleShapeData(50.0f));
	canvas->AddChild(_image);*/

	ARectangleActor* _rectangle = SpawnActor<ARectangleActor>(Vector2f(50.0f, 50.0f));
	_rectangle->SetLocation(Vector2f(100.0f, 100.0f));
	_rectangle->AddComponent(new UCollisionComponent(_rectangle, "Caca", IS_ALL, CT_BLOCK));

	ACircleActor* _circle = SpawnActor<ACircleActor>(50.0f);
	_circle->SetLocation(Vector2f(100.0f, 200.0f));
	_circle->AddComponent(new UCollisionComponent(_circle, "Caca", IS_ALL, CT_BLOCK));


	const vector<pair<string, CollisionType>>& _responses
	{
		{"Player", CT_BLOCK},
		{"Asteroid", CT_OVERLAP},
		{"UFO", CT_BLOCK},
		{"Projectile", CT_OVERLAP},
	};
	_circle->GetComponent<UCollisionComponent>()->AddResponses(_responses);
	_rectangle->GetComponent<UCollisionComponent>()->AddResponses(_responses);

	//GetGameMode()->GetHUD()->AddToViewport(canvas);
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
