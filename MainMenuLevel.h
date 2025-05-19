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

class UMainMenuLevel : public Level
{
	UI::CanvasWidget* mainMenuCanvas;
	UI::CanvasWidget* optionCanvas;
	UI::CanvasWidget* leaderBoardCanvas;
	UI::CanvasWidget* startCanvas;
	UI::CanvasWidget* creditCanvas;

public:
	UMainMenuLevel(const string& _levelName);

protected:
	virtual void InitLevel() override;

	void InitMainMenu(HUD* _hud);
	void InitOptionMenu(HUD* _hud);
	void InitLeaderBoardMenu(HUD* _hud);
	void InitStartMenu(HUD* _hud);
	void InitCreditMenu(HUD* _hud);

	ButtonWidget* InitButtonAndLabelData(HUD* _hud, UI::CanvasWidget* _canva, const FButtonAndLabelData& _data);
	void OpenMenu(UI::CanvasWidget* _canvaToOpen, UI::CanvasWidget* _canvaToClose);
};