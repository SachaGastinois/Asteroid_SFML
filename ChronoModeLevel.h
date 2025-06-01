#pragma once

#include "GameplayLevel.h"
#include "CanvasWidget.h"
#include "GIFWidget.h"
#include "ButtonWidget.h"
#include "ImageWidget.h"
#include "LabelWidget.h"
#include "TextObject.h"

class UChronoModeLevel : public UGameplayLevel
{
	UI::ACanvasWidget* timesUpCanvas;
	UI::ALabelWidget* timerLabel;

	float currentTime;
	float baseTime;

	float currentSpawnTime;
	float spawnTime;

	bool isTimerRunning;
public:
	FORCEINLINE void SetTimerRunning(const bool _status) { isTimerRunning = _status; }
public:
	UChronoModeLevel(const string& _levelName);
protected:
	virtual void InitLevel() override;
	virtual void Update(const float _deltaTime) override;

	virtual void InitGameplayCanvas(HUD* _hud) override;
	void InitTimesUpCanvas(HUD* _hud);

	string TimerToString();
	void UpdateTimer(const float _deltaTime);
	void UpdateSpawnTimer(const float _deltaTime);
	void OnTimerFinished();

	void SpawnAsteroid();
	void SpawnUFO();
	virtual void Reset() override;
};

