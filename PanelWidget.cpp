#include "PanelWidget.h"

UI::PanelWidget::PanelWidget(Level* _level, const string& _name, const RenderType& _type) : AWidget(_level, _name, _type)
{
	maxChild = 32768;
	size = { 64.0f, 64.0f };
	debugMode = false;
	debugFrame = VertexArray(PrimitiveType::LineStrip, 5);
	debugFrame[0].color = Color(255, 0, 0);
	debugFrame[1].color = Color(255, 255, 0);
	debugFrame[2].color = Color(0, 255, 0);
	debugFrame[3].color = Color(0, 255, 255);
	debugFrame[4].color = Color(0, 0, 255);

	UpdateDebugFrame();
}


void UI::PanelWidget::UpdateDebugFrame()
{
	debugFrame[0].position = Vector2f(GetLocation());
	debugFrame[1].position = Vector2f(size.x, GetLocation().y);
	debugFrame[2].position = Vector2f(size.x, size.y);
	debugFrame[3].position = Vector2f(GetLocation().x, size.y);
	debugFrame[4].position = debugFrame[0].position;
}


void UI::PanelWidget::Render(RenderWindow& _window)
{
	if (debugMode)
	{
		_window.draw(debugFrame);
	}
}