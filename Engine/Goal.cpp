#include "Goal.h"

Goal::Goal(std::mt19937 & rng, const Board & brd, const Snake & snek)
{
	Respawn(rng, brd, snek);
}

void Goal::Respawn(std::mt19937 & rng, const Board & brd, const Snake & snek)
{
	std::uniform_int_distribution<int> xDist(2, brd.GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(3, brd.GetGridHeight() - 1);

	Location newLoc;
	do 
	{
		newLoc.X = xDist(rng);
		newLoc.Y = yDist(rng);
	} while (snek.IsInTile(newLoc));
	loc = newLoc;
}

void Goal::Draw(Board & brd) const
{
	brd.DrawCell(loc, c, 0);
}

const Location & Goal::GetLocation() const
{
	return loc;
}
