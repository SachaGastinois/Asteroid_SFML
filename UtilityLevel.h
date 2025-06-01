#pragma once
#include "Level.h"
#include "CanvasWidget.h"
#include "ButtonWidget.h"
#include "TextObject.h"

struct FButtonAndLabelData
{
	string text;
	string labelName;
	string buttonName;
	string buttonPath;
	Vector2f location;
	Vector2f size;
	pair<string, FontExtensionType> fontData;
	int characterSize;
	int zOrder;

	FButtonAndLabelData() = default;
	FButtonAndLabelData(const string& _text, const string& _labelName, const string& _buttonName, const string& _buttonPath,
		const Vector2f& _location, const Vector2f& _size, const pair<string, FontExtensionType>& _fontData,
		const int _characterSize, const int _zOrder)
	{
		text = _text;
		labelName = _labelName;
		buttonName = _buttonName;
		buttonPath = _buttonPath;
		location = _location;
		size = _size;
		fontData = _fontData;
		characterSize = _characterSize;
		zOrder = _zOrder;
	}
};

class UUtilityLevel : public Level
{
protected:
	Vector2f windowSize;
public:
	UUtilityLevel(const string& _levelName);
protected:
	virtual void InitLevel() override;

	AButtonWidget* InitButtonAndLabelData(HUD* _hud, UI::ACanvasWidget* _canva, const FButtonAndLabelData& _data);
public:
	void OpenMenu(UI::ACanvasWidget* _canvaToOpen, UI::ACanvasWidget* _canvaToClose);
};

