#pragma once

class Location
{
public:
	void Add(const Location& val)
	{
		X += val.X;
		Y += val.Y;
	}
	bool operator==(const Location& rhs)const
	{
		return X == rhs.X && Y == rhs.Y;
	}
	int X;
	int Y;
};