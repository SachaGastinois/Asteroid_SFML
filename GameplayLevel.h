#pragma once

#include "UtilityLevel.h"
#include "LabelWidget.h"
#include "GIFWidget.h"

class UGameplayLevel : public UUtilityLevel
{

protected:
	UI::ACanvasWidget* pauseCanvas;
	UI::ACanvasWidget* gameplayCanvas;
	UI::ACanvasWidget* ugradeCanvss;

	UI::AGIFWidget* backgroundGIF;

	vector<UI::AImageWidget*> lifesWidgets;
	UI::ALabelWidget* scorePointLabel;
	int currentScorePoint;

	bool isPause;

public:
	FORCEINLINE UI::ACanvasWidget* GetPauseCanvas() { return pauseCanvas; }
	FORCEINLINE void SetIsPause(const bool _status) { isPause = _status; }
	FORCEINLINE bool GetIsPause() { return isPause; }
	FORCEINLINE void AddPoints(const int _pointToAdd)
	{
		if (!scorePointLabel) return;

		currentScorePoint += _pointToAdd;
		scorePointLabel->SetText(to_string(currentScorePoint));
	}

public:
	UGameplayLevel();
	UGameplayLevel(const string& _levelName);

protected:
	virtual void InitLevel() override;
	virtual void Update(const float _deltaTime) override;

	void InitPauseMenu(HUD* _hud);
	void InitGameplayCanvas(HUD* _hud);
	void InitUpgradeMenu(HUD* _hud);
	void InitBackgroundGIF(HUD* _hud);
	void InitMainMenuTheme();

	void SetLocationIfOutOfBoundes(AActor* _actor);

};

