#include "HUD.h"
#include "CameraManager.h"
#include "Level.h"

using namespace UI;
using namespace Camera;

UI::HUD::HUD(Level* _level) : AActor(_level)
{
	allWidgets = set<Widget*>();
	currentWidget = nullptr;
}

UI::HUD::HUD(const HUD& _other) : AActor(_other)
{
	for (Widget* _widget : _other.allWidgets)
	{
		allWidgets.insert(_widget);
	}

	currentWidget = _other.currentWidget;
}


void UI::HUD::AddToViewport(Widget* _widget)
{
	for (Widget* _selectedWidget : allWidgets)
	{
		RemoveFromViewport(_selectedWidget);
	}
	currentWidget = _widget;
	currentWidget->BindViewport();
}

void UI::HUD::RemoveFromViewport(Widget* _widget)
{
	for (AActor* _actor : _widget->GetChildren())
	{
		if (Widget* _selectedWidget = Cast<Widget>(_actor))
		{
			RemoveFromViewport(_selectedWidget);
		}
	}
	_widget->UnbindViewport();
	currentWidget = nullptr;
}