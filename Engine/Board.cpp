#include "Board.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{}

void Board::DrawCell(const Location& loc, Color c,int modifications)
{
	
	
	gfx.DrawRectDim(loc.X * Dimensions - modifications, loc.Y * Dimensions - modifications, Dimensions, Dimensions, modifications, c);
}

int Board::GetGridWidth() const
{
	return Width;
}

int Board::GetGridHeight() const
{
	return Height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.X >= 2 && loc.X < 38 &&
		   loc.Y >= 3. && loc.Y < 27;
}

void Board::DrawBorder(const Color c)
{
	gfx.DrawBorder(40 , 60 , Width*Dimensions, Height*Dimensions, c);
}
