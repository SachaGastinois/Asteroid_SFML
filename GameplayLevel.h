#pragma once

#include "UtilityLevel.h"
#include "LabelWidget.h"
#include "GIFWidget.h"

class APlayerPawn;

class UGameplayLevel : public UUtilityLevel
{

protected:
	UI::ACanvasWidget* pauseCanvas;
	UI::ACanvasWidget* gameplayCanvas;
	UI::ACanvasWidget* gameOverCanvas;

	UI::AGIFWidget* backgroundGIF;

	vector<UI::AImageWidget*> lifesWidgets;
	UI::ALabelWidget* scorePointLabel;
	int currentScorePoint;

	bool isPause;

	APlayerPawn* player;

public:
	FORCEINLINE UI::ACanvasWidget* GetPauseCanvas() { return pauseCanvas; }
	FORCEINLINE UI::ACanvasWidget* GetGameOverCanvas() { return gameOverCanvas; }
	FORCEINLINE void SetIsPause(const bool _status) { isPause = _status; }
	FORCEINLINE bool GetIsPause() { return isPause; }
	FORCEINLINE void AddPoints(const int _pointToAdd)
	{
		if (!scorePointLabel) return;

		currentScorePoint += _pointToAdd;
		scorePointLabel->SetText(to_string(currentScorePoint));
		scorePointLabel->SetOriginAtMiddle();
	}

public:
	UGameplayLevel(const string& _levelName);

protected:
	virtual void InitLevel() override;
	virtual void Update(const float _deltaTime) override;

	void InitPauseMenu(HUD* _hud);
	virtual void InitGameplayCanvas(HUD* _hud);
	void InitGameOverCanvas(HUD* _hud);
	void InitBackgroundGIF(HUD* _hud);
	void InitGameplayTheme();

	void SetLocationIfOutOfBoundes(AActor* _actor);
public:
	void UpdatePlayerLife();
	virtual void Reset();
};

