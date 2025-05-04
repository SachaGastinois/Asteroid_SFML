#include "Box.h"
#include "Level.h"
#include "HUD.h"

UI::Box::Box(Level* _level, const BoxData& _data) : AWidget(_level, "AWidget")
{
	widgets = vector<AWidget*>();
	data = _data;
}


void UI::Box::AddWidget(AWidget* _widget)
{
	widgets.push_back(_widget);
	AddChild(_widget, AT_KEEP_RELATIVE);
	Update();

	hud->AddToViewport(_widget);
}

void UI::Box::RemoveWidget(AWidget* _widget)
{
	using Iterator = vector<AWidget*>::iterator;
	for (Iterator _it; _it != widgets.end(); ++_it)
	{
		if (*_it == _widget)
		{
			widgets.erase(_it);
			break;
		}
	}

	RemoveChild(_widget);
	Update();

	hud->RemoveFromViewport(_widget);
}