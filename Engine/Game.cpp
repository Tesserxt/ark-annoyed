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


Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ball(Vec2(390.0f, 390.0f), Vec2(60.0f * 2, 60.0f * 3)),
	walls( 0.0, float(Graphics::ScreenWidth), 0, float(Graphics::ScreenHeight) ),
	pad( Vec2( 400.0f, 400.0f), 50.0f, 10.0f),
	soundpad( L"Sounds\\arkpad.wav"),
	soundbrick( L"Sounds\\arkbrick.wav")
	
{
	float p = (Graphics::ScreenWidth - ( brickwidth * float(nBricksAcross) )) / 2.0f;
	Vec2  topleft(p, brickheight );
	Color Colors[nBricksDown] = { Colors::Red, Colors::Green, Colors::Blue,Colors::Yellow, Colors::Cyan };
	int i = 0;
	for (int y = 0; y < nBricksDown; y++)
	{
		Color c = Colors[y];
		for (int x = 0; x < nBricksAcross; x++)
		{
			brick[i] =  Brick( RectF(
						topleft + Vec2( x * brickwidth, y * brickheight),
						brickwidth, brickheight), 
						c);
			i++;
		}
	}
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
	float dt = ft.Mark();
	pad.Update( wnd.kbd, dt);
	pad.IsWallColliding(walls);
	ball.Update(dt);

	for (Brick& b : brick)
	{
		if (b.IsBallColliding(ball))
		{
			soundbrick.Play();
		}
	}
	if (pad.IsBallColliding(ball))
	{
		soundpad.Play();
	}
	if (ball.IsColliding(walls))
	{
		soundpad.Play();
	}
}

void Game::ComposeFrame()
{	
	for (Brick& b : brick)
	{
		b.Draw(gfx);
	}
	pad.Draw(gfx);
	ball.Draw(gfx);
}
