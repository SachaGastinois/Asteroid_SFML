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

	UI::AGIFWidget* movementEffectGIF;
	UI::AGIFWidget* movementEffectGIF1;
	UI::AGIFWidget* movementEffectGIF2;
	UI::AGIFWidget* movementEffectGIF3;


public:
	UClassicModeLevel(const string& _levelName);
protected:
	virtual void InitLevel() override;

};

