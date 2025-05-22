#pragma once
#include "UtilityLevel.h"
#include "CanvasWidget.h"
#include "ButtonWidget.h"
#include "TextObject.h"

class UMainMenuLevel : public UUtilityLevel
{
	UI::CanvasWidget* mainMenuCanvas;
	UI::CanvasWidget* optionCanvas;
	UI::CanvasWidget* leaderBoardCanvas;
	UI::CanvasWidget* startCanvas;
	UI::CanvasWidget* creditCanvas;

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
};