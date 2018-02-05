#include "Score.h"

Score::Score(Graphics & gfx)
	:
	gfx(gfx)
{}

void Score::Draw(int score, Color c)
{
	gfx.DrawRectDim(40, 10, score * 14.5, 30, 0, c);
}

