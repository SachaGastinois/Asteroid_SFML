#pragma once

#include "GameplayLevel.h"
#include "CanvasWidget.h"
#include "GIFWidget.h"
#include "ButtonWidget.h"
#include "ImageWidget.h"
#include "LabelWidget.h"
#include "TextObject.h"

class UClassicModeLevel : public UGameplayLevel
{
	UI::ACanvasWidget* upgradeCanvas;

	int difficulty;
	int asteroidBaseCount;
	int ufoBaseCount;

	int entityLeft;
	bool isWaveOnGoing;
public:
	FORCEINLINE void DecrementEntityLeft() { entityLeft--; LOG(Display, to_string(entityLeft)); }
public:
	UClassicModeLevel(const string& _levelName);
protected:
	virtual void InitLevel() override;
	virtual void Update(const float _deltaTime) override;
	void InitUpgradeMenu(HUD* _hud);

	void StartWave();
	void OnWaveOver();
	void SpawnAsteroid();
	void SpawnUFO();
	virtual void Reset() override;
};

