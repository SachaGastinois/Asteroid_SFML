#pragma once
#include "UtilityLevel.h"
#include "CanvasWidget.h"
#include "ButtonWidget.h"
#include "TextObject.h"
#include "GIFWidget.h"
#include "SliderWidget.h"

class UMainMenuLevel : public UUtilityLevel
{
	UI::AGIFWidget* backgroundGIF;

	UI::ACanvasWidget* mainMenuCanvas;
	UI::ACanvasWidget* optionCanvas;
	UI::ACanvasWidget* leaderBoardCanvas;
	UI::ACanvasWidget* startCanvas;
	UI::ACanvasWidget* creditCanvas;

	UI::SliderWidget* sliderBar;

public:
	UMainMenuLevel(const string& _levelName);

protected:
	virtual void InitLevel() override;
	virtual void Update(const float _deltaTime) override;

	void InitMainMenu(HUD* _hud);
	void InitOptionMenu(HUD* _hud);
	void InitLeaderBoardMenu(HUD* _hud);
	void InitStartMenu(HUD* _hud);
	void InitCreditMenu(HUD* _hud);

	void InitBackgroundGIF(HUD* _hud);
	void InitMainMenuTheme();
};