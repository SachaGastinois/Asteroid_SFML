#include "HUD.h"
#include "CameraManager.h"
#include "Level.h"

using namespace UI;
using namespace Camera;

UI::HUD::HUD(Level* _level) : AActor(_level)
{
	allWidgets = set<AWidget*>();
	currentWidget = nullptr;
}

UI::HUD::HUD(const HUD& _other) : AActor(_other)
{
	for (AWidget* _widget : _other.allWidgets)
	{
		allWidgets.insert(_widget);
	}

	currentWidget = _other.currentWidget;
}


void UI::HUD::AddToViewport(AWidget* _widget)
{
	for (AWidget* _selectedWidget : allWidgets)
	{
		RemoveFromViewport(_selectedWidget);
	}
	currentWidget = _widget;
	currentWidget->BindViewport();
}

void UI::HUD::RemoveFromViewport(AWidget* _widget)
{
	for (AActor* _actor : _widget->GetChildren())
	{
		if (AWidget* _selectedWidget = Cast<AWidget>(_actor))
		{
			RemoveFromViewport(_selectedWidget);
		}
	}
	_widget->UnbindViewport();
	currentWidget = nullptr;
}