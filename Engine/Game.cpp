/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	rng(std::random_device()()),
	snek({ 20,15 }),
	goal(rng, brd, snek),
	score(gfx)

{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (GameIsStarted && !GameIsOver)
	{
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			if (Delta_loc.Y != 1 && CanMove || snek.GetSize()<=2 && CanMove)
			{
				Delta_loc = { 0,-1 };
				CanMove = false;

			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_DOWN))
		{
			if (Delta_loc.Y != -1 && CanMove || snek.GetSize()<=2 && CanMove)
			{
				Delta_loc = { 0,1 };
				CanMove = false;
			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
		{
			if (Delta_loc.X != -1 && CanMove || snek.GetSize()<=2 && CanMove)
			{
				Delta_loc = { 1,0 };
				CanMove = false;
			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_LEFT))
		{
			if (Delta_loc.X != 1 && CanMove || snek.GetSize()<=2 && CanMove)
			{
				Delta_loc = { -1,0 };
				CanMove = false;
			}
		}
		int snekSpeed = snekMovePeriod;
		if ( (snek.GetSize() - 4) <=5)
		{
			snekSpeed -= (snek.GetSize()-4); 
		}
		else
		{
			snekSpeed = 10;
		}
		++snekMoveCounter;
		if (snekMoveCounter >= snekSpeed)
		{
			CanMove = true;
			if (snek.GetSize() <= 3)
			{
				snek.grow();
			}
			snekMoveCounter = 0;
			
			const Location Next = snek.GetNextHeadLocation(Delta_loc);
			for (int i = 0; i <= nObstacles; i++)
			{
				const bool IsDead = (Next == obstacle[i].GetLocation());
				if (IsDead)
				{
					GameIsOver = true;
				}
				else
				{

				}
			}
			if (!brd.IsInsideBoard(Next) || 
				snek.IsInTileExceptEnd(Next)||
				snek.GetSize()>=55 )
			{
				GameIsOver = true;
			}
			else if (!GameIsOver)
			{
				const bool IsEating = (Next == goal.GetLocation());
				if (IsEating)
				{
					snek.grow();
					if (nObstacles < 19)
					{
						nObstacles++;
						obstacle[nObstacles].Spawn(rng, brd, snek);
					}
				
				}
				snek.MoveBy(Delta_loc);
					 
				
				if (IsEating)
				{
					goal.Respawn(rng, brd, snek);
				}
			}
		}
	}
	if (!GameIsStarted)
	{
		if (wnd.kbd.KeyIsPressed(VK_RETURN))
			GameIsStarted = true;
	}

}

void Game::ComposeFrame()
{
	if (GameIsStarted)
	{
		if (snek.GetSize() <= 4)
		{
			Color Border = Colors::White;
			brd.DrawBorder(Border);
		}
		else
		{
			Color Border = Colors::MakeRGB(255 - (snek.GetSize() - 4) * 5, 255, 255 - (snek.GetSize() - 4) * 5);
			brd.DrawBorder(Border);
			score.Draw(snek.GetSize() - 4, Border);
		}

		for (int i = 0; i <= nObstacles; i++)
		{
			obstacle[i].Draw(brd);
		}
		snek.Draw(brd);
		goal.Draw(brd);
		if (GameIsOver)
		{
			SpriteCodex::DrawGameOver(200, 200, gfx);
		}
	}
	else
	{
		Color Border = Colors::White;
		SpriteCodex::DrawTitle(300, 200, gfx);
		brd.DrawBorder(Border);
	}

}
