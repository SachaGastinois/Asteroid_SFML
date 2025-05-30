#pragma once
#include "UtilityLevel.h"
#include "CanvasWidget.h"
#include "GIFWidget.h"
#include "ButtonWidget.h"
#include "ImageWidget.h"
#include "LabelWidget.h"
#include "TextObject.h"


class UClassicModeLevel : public UUtilityLevel
{
	UI::ACanvasWidget* pauseCanvas;
	UI::ACanvasWidget* gameplayCanvas;
	UI::ACanvasWidget* ugradeCanvss;

	UI::AGIFWidget* movementEffectGIF;
	UI::AGIFWidget* backgroundGIF;
	UI::AGIFWidget* movementEffectGIF1;
	UI::AGIFWidget* movementEffectGIF2;
	UI::AGIFWidget* movementEffectGIF3;

	vector<UI::AImageWidget*> lifesWidgets;
	UI::ALabelWidget* scorePointLabel;
	int currentScorePoint;

public:
	UClassicModeLevel(const string& _levelName);
protected:
	virtual void InitLevel() override;

	void InitPauseMenu(HUD* _hud);
	void InitGameplayCanvas(HUD* _hud);
	void InitUpgradeMenu(HUD* _hud);

	void InitBackgroundGIF(HUD* _hud);
	void InitMainMenuTheme();


};

