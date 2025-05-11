#include "Widget.h"
#include "CameraManager.h"
#include "Level.h"

using namespace Camera;
using namespace Input;

UI::AWidget::AWidget(Level* _level, const string& _name, const RenderType& _type) : AActor(_level, _name)
{
	type = _type;
	visibility = Visible;
	renderToken = 0;
	slot = nullptr;
	hud = _level->GetGameMode()->GetHUD();
}

UI::AWidget::~AWidget()
{
	delete slot;
}

void UI::AWidget::Construct()
{
	Super::Construct();

	if (PlayerController* _playerController = GetLevel()->GetGameMode()->GetPlayerController<PlayerController>())
	{
		InputManager& _inputManager = _playerController->GetInputManager();
		BindActions(_inputManager);
	}
}

void UI::AWidget::BindViewport()
{
	for (AActor* _actor : GetChildren())
	{
		if (AWidget* _widget = Cast<AWidget>(_actor))
		{
			_widget->BindViewport();
		}
	}
	const FRenderData& _data = FRenderData(bind(&AWidget::Render, this, _1), type);
	renderToken = level->GetCameraManager().BindOnRenderWindow(_data, zOrder);
}

void UI::AWidget::UnbindViewport()
{
	level->GetCameraManager().UnbindOnRenderWindow(renderToken);
}

void UI::AWidget::SetZOrder(const int _zOrder)
{
	Super::SetZOrder(_zOrder);

	level->GetCameraManager().SetZOrder(renderToken, _zOrder);
}