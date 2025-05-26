#pragma once
#include "Level.h"
#include "CUSTOMGameMode.h"

#include "CanvasWidget.h"
#include "LabelWidget.h"
#include "ImageWidget.h"

class CUSTOMLevel : public Level
{
	ACanvasWidget* canvas;
	ALabelWidget* label;
	AImageWidget* image;

public:
	FORCEINLINE virtual CUSTOMGameMode* GetGameModeRef() override
	{
		return new CUSTOMGameMode(this);
	}
	
public:
	CUSTOMLevel(const string& _name);

protected:
	virtual void InitLevel() override;
};