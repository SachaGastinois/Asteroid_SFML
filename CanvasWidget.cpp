#include "CanvasWidget.h"

UI::ACanvasWidget::ACanvasWidget(Level* _level, const string& _name, const RenderType& _type) : PanelWidget(_level, _name, _type)
{
	size = { 400.0f, 300.0f };
}


void UI::ACanvasWidget::Construct()
{
	Super::Construct();

	if (debugMode)
	{
		LOG(Warning, "DebugMode enabled on Canvas \"" + GetName() + "\"");
	}
}

void UI::ACanvasWidget::Render(RenderWindow& _window)
{
	Super::Render(_window);
}

