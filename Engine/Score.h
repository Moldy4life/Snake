#pragma once

#include "graphics.h"
class Score
{
public:
	Score(Graphics& gfx);
	void Draw(int score, Color c);
private:
	Graphics & gfx;
};