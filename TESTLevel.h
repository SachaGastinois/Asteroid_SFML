#pragma once
#include "Level.h"

class ACanvasWidget;

class TESTLevel : public Level
{

public:
	TESTLevel(const string& _levelName);

protected:
	virtual void InitLevel() override;
	virtual void Update(const float _deltaTime) override;

	virtual void Load() override;
	virtual void Unload() override;
	void SetLocationIfOutOfBoundes(AActor* _actor);
};