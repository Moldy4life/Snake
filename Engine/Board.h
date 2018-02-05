#pragma once

#include "Graphics.h"
#include "Location.h"
class Board
{
public:
	Board(Graphics& gfx);
	void DrawCell(const Location& loc, Color c, int modifications);
	int GetGridWidth()const;
	int GetGridHeight()const;
	bool IsInsideBoard(const Location& loc)const;
	void DrawBorder(const Color c);
	
private:
	static constexpr int Dimensions = 20;
	static constexpr int Width = 38;
	static constexpr int Height = 27;
	Color c = Colors::MakeRGB(255,255,255);
	Graphics& gfx;
};
