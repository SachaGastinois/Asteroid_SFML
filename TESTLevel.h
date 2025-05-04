#pragma once
#include "Level.h"
#include "CanvasWidget.h"

class TESTLevel : public Level
{
	UI::CanvasWidget* mainMenuCanvas = nullptr;
	UI::CanvasWidget* optionCanvas = nullptr;

public:
	TESTLevel(const string& _levelName);

protected:
	virtual void InitLevel() override;

	void InitMainMenu(HUD* _hud);
	void InitOptionMenu(HUD* _hud);
	void OpenMenu(UI::CanvasWidget* _canvaToOpen, UI::CanvasWidget* _canvaToClose);
};