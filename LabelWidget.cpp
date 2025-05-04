#include "LabelWidget.h"

UI::ALabelWidget::ALabelWidget(Level* _level, const string& _text, const string& _name, const RenderType& _type) : AWidget(_level, _name, _type)
{
	text = new TextObject(_text, "Default", OTF);
}

UI::ALabelWidget::~ALabelWidget()
{
	delete text;
}


string UI::ALabelWidget::ComputeScoreText()
{
	stringstream _ss;
	_ss << setw(scoreMaxDigit) << setfill('0') << score;

	return _ss.str();
}


void UI::ALabelWidget::Render(RenderWindow& _window)
{
	if (visibility == Hidden) return;
	_window.draw(*text->GetDrawable());
	if (slot && slot->GetDebugMode())
	{
		slot->RenderDebugFrame(_window);
	}
}

void UI::ALabelWidget::UpdatePosition(const Vector2f _position)
{
	if (slot)
	{
		slot->SetLocation(_position);
		Super::SetLocation(slot->GetLocation());
		text->SetLocation(_position);
	}
	else
	{
		Super::SetLocation(_position);
		text->SetLocation(_position);
	}
}

void UI::ALabelWidget::UpdateMove(const Vector2f& _offset)
{
	if (slot)
	{
		slot->SetLocation(GetLocation());
		Super::Move(_offset);
		text->Move(_offset);
	}

	else
	{
		Super::Move(_offset);
		text->Move(_offset);
	}
}