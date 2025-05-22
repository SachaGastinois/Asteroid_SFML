#pragma once
#include "UtilityLevel.h"
#include "CanvasWidget.h"
#include "ButtonWidget.h"
#include "TextObject.h"


class UClassicModeLevel : public UUtilityLevel
{
	UI::CanvasWidget* pauseMenu;

public:
	UClassicModeLevel(const string& _levelName);
protected:
	virtual void InitLevel() override;

	void InitPauseMenu(HUD* _hud);

};

