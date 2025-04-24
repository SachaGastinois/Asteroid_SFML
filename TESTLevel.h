#pragma once
#include "Level.h"

class TESTLevel : public Level
{

public:
	TESTLevel(const string& _levelName);

protected:
	virtual void InitLevel() override;
};