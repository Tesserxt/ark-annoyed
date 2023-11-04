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
	ball(Vec2(410.0f, 480.0f),  Vec2( 0, -1.0f) ),
	walls( RectF(brdx + dim, brdx + dim*brdwidth, dim, dim*dim), 8.0f, {230, 0, 230}),
	pad( Vec2( 410.0f, 500.0f), 50.0f, 10.0f),
	rng(std::random_device()()),
	
	soundpad( L"Sounds\\arkpad.wav"),
	soundbrick( L"Sounds\\arkbrick.wav"),
	soundobstacle( L"Sounds\\fart1.wav"),
	soundgameover( L"Sounds\\arkGameOver.wav"),
	soundObstacle( L"Sounds\\obstacle.wav"),
	soundGameStart( L"Sounds\\GameStart.wav")
	
{
	
	Vec2  topleft(topleftX, 50 );
	int i = 0;
	for (int y = 0; y < nBricksDown; y++)
	{
		Color c = brickColors[y];
		for (int x = 0; x < nBricksAcross; x++)
		{
			Vec2 pos = topleft + Vec2(x * brickwidth, y * brickheight);
			brick[i] =  Brick( RectF(pos, brickwidth, brickheight), c);
			i++;
		}
	}
	std::uniform_real_distribution<float> xDist( 235.0f, 500.0f );
	std::uniform_real_distribution<float> yDist( 30.0f,  60.0f  );
	for (int i = 0; i < nObstacles; i++)
	{
		obstacle[i] = Obstacle(Vec2( xDist( rng ), yDist( rng ) ), Vec2(60.0f / 2.0f * 0.0f, 60.0f * 1.0f));
	}
	brk = Brick(RectF(50, 150, 50, 100), Colors::LightGray);
}

void Game::Go()
{
	gfx.BeginFrame();
	float elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}

	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel( float dt )
{	
	if (wnd.kbd.KeyIsPressed(VK_RETURN) && !inhibitReturn)
	{
		GameStart = true;
		Ready = true;
		inhibitReturn = true;
	}

	if (inhibitReturn)
	{
		soundGameStart.Play();
		inhibitReturn = false;
	}

	if (!GameOver && GameStart && !(nBricksDestroyed == nBricks) )
	{	
		bool collisionHappend = false;
		float curColDistSq;
		int curColIndex;

		for (int i = 0; i < nBricks; i++)
		{
			if (brick[i].IsBallColliding(ball))
			{
				float newColDistSq = (ball.GetPos() - brick[i].GetCenter()).GetLengthSq();
				if (collisionHappend)
				{
					if (newColDistSq < curColDistSq)
					{
						curColDistSq = newColDistSq;
						curColIndex = i;
					}
				}
				else
				{
					curColDistSq = newColDistSq;
					curColIndex = i;
					collisionHappend = true;
				}
			}
		}

		if (collisionHappend)
		{
			nBricksDestroyed++;
			pad.ResetCoolDown();
			brick[curColIndex].ExecuteBallColliding(ball);
			soundbrick.Play();
		}

		pad.Update(wnd.kbd, dt);
		pad.IsWallColliding(walls.GetInnerBounds());
		ball.Update(dt);	
		int i = x;
		if( i == x )
		{
			obstacle[x].Update(dt);
			if (obstacle[x].IsBallColliding(ball))
			{	
				pad.ResetCoolDown();
			}
			if (obstacle[x].IsWallColliding(walls.GetInnerBounds()))
			{
				x++;
			}
			if (obstacle[x].IsPadColliding(pad.GetRect()))
			{
				soundgameover.Play();
				obstacle[x].destroyed = true;
				GameStart = false;
				ball = Ball(Vec2(410.0f, 480.0f), Vec2(0, -1.0f ));
				pad = Paddle(Vec2(410.0f, 500.0f), 50.0f, 10.0f);
				lives--;
				x++;
			}
			i++;
		}		
		
		if (pad.IsBallColliding(ball))
		{
			soundpad.Play();
		}
		if (ball.IsColliding(walls.GetInnerBounds()))
		{
			GameOver = ball.isGameOver(walls.GetInnerBounds(), lives);
			if (ball.GetPos().y + 7.0f >= walls.GetInnerBounds().bottom)
			{
				soundgameover.Play(); 
				inhibitReturn = false;
				GameStart = false;
				ball = Ball(Vec2(410.0f, 480.0f), Vec2( 0, -1.0f ));
				pad  = Paddle(Vec2(410.0f, 500.0f), 50.0f, 10.0f);
			}
			else
			{	
				pad.ResetCoolDown();
				soundpad.Play();
			}
		}
	}
}

void Game::ComposeFrame()
{
	walls.Draw(gfx);
	//SpriteCodex::DrawPooBoard( brdx, brdwidth, gfx);
	for (Brick& b : brick)
	{
		b.Draw(gfx);
	}
	
	if (!GameStart && !GameOver)
	{
		SpriteCodex::DrawReady(Graphics::GetScreenRect().GetCenter(), gfx);
	}

	if (GameStart && lives > 0 && !GameOver)
	{
		pad.Draw(gfx);
		ball.Draw(gfx);
	}

	obstacle[x].Draw(gfx);
	
	for( int i = 1; i <= lives; i++)
	{
		SpriteCodex::DrawBall(Vec2( 15 * i, 10), gfx);
	}
	if (GameOver)
	{
		SpriteCodex::DrawGameOver(Vec2(400.0f, 300.0f), gfx);
	}
	
}
