#pragma once

#include "Board.h"

class Snake
{
private:
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody1();
		void InitBody2();
		void InitBody3();
		void Follow(const Segment& next);
		void MoveBy(const Location& in_loc);
		void Draw(Board& brd);
		const Location& GetLocation()const;
	private:
		Location loc;
		Color c;
		int DimMod;
		
	};

public:
	Snake(const Location& in_loc);
	void MoveBy(const Location& delta_loc);
	Location GetNextHeadLocation(const Location& delta_loc)const;
	void grow();
	void Draw(Board& brd);
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;
	int GetSize()const;

private:
	static constexpr Color ColorHead = Colors::Yellow;
	static constexpr Color ColorBody1 = Colors::MakeRGB(0, 100, 0);
	static constexpr Color ColorBody2 = Colors::MakeRGB(0, 175, 0);
	static constexpr Color ColorBody3 = Colors::MakeRGB(0, 250, 0);
	static constexpr int nSegmentsMax = 100;
	Segment segments[nSegmentsMax];
	int nSegments = 1;
	int counter = 0;
	
};