#pragma once
#include "UtilityLevel.h"
#include "CanvasWidget.h"
#include "ButtonWidget.h"
#include "TextObject.h"
#include "GIFWidget.h"

class UMainMenuLevel : public UUtilityLevel
{
	UI::AGIFWidget* backgroundGIF;

	UI::ACanvasWidget* mainMenuCanvas;
	UI::ACanvasWidget* optionCanvas;
	UI::ACanvasWidget* leaderBoardCanvas;
	UI::ACanvasWidget* startCanvas;
	UI::ACanvasWidget* creditCanvas;

	Vector2f windowSize;

public:
	UMainMenuLevel(const string& _levelName);

protected:
	virtual void InitLevel() override;

	void InitMainMenu(HUD* _hud);
	void InitOptionMenu(HUD* _hud);
	void InitLeaderBoardMenu(HUD* _hud);
	void InitStartMenu(HUD* _hud);
	void InitCreditMenu(HUD* _hud);

	void InitBackgroundGIF(HUD* _hud);
	void InitMainMenuTheme();
};