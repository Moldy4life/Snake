#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & in_loc)
{
	segments[0].InitHead(in_loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = nSegments - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

Location Snake::GetNextHeadLocation(const Location & delta_loc) const
{
	Location L(segments[0].GetLocation());
	L.Add(delta_loc);
	return L;
}

void Snake::grow()
{
	if (nSegments < nSegmentsMax)
	{
		if (counter == 0 || counter == 3)
		{
			counter = 0;
			counter += 1;
			segments[nSegments].InitBody1();
		}
		else if (counter == 1)
		{
			counter += 1;
			segments[nSegments].InitBody2();
		}
		else if (counter == 2)
		{
			counter += 1;
			segments[nSegments].InitBody3();
		}
		nSegments++;
	}
}

void Snake::Draw(Board & brd)
{
	for (int i = 0; i < nSegments; i++)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::IsInTileExceptEnd(const Location & target) const
{
	for (int i = 0; i < nSegments-1; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
		
	}
	return false;
}

bool Snake::IsInTile(const Location & target) const
{
	for (int i = 0; i < nSegments; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}

	}
	return false;
}

int Snake::GetSize()const
{
	return nSegments;
}

void Snake::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::ColorHead;
	DimMod = 0;
}

void Snake::Segment::InitBody1()
{
	c = Snake::ColorBody1;
	DimMod = -1;
}

void Snake::Segment::InitBody2()
{
	c = Snake::ColorBody2;
	DimMod = -1;
}

void Snake::Segment::InitBody3()
{
	c = Snake::ColorBody3;
	DimMod = -1;
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	assert(abs(delta_loc.X) + abs(delta_loc.Y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board& brd) 
{
	brd.DrawCell(loc, c, DimMod);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
