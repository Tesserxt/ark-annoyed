/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Brick.h"
#include "RectF.h"
#include "Ball.h"
#include "FrameTimer.h"
#include "Sound.h"
#include "Paddle.h"
#include "SpriteCodex.h"
#include "Obstacle.h"
#include "Beveler.h"
#include <random>

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel( float dt);
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	
	float brickwidth  =  45.0f;
	float brickheight =  20.0f;
	static constexpr int nBricksAcross = 7;
	static constexpr int nBricksDown = 5;
	static constexpr int nBricks = nBricksAcross * nBricksDown;
	static constexpr int nObstacles = 20;
	static constexpr Color brickColors[nBricksDown] = { {230, 0, 0}, {0, 230, 0}, {0, 0, 230}, {230, 230, 0}, {0, 230, 230} };
	int nBricksDestroyed = 0;

	float dim = 24.0f; // poo dimension 24*24
	float brdx = 208.0f;
	float brdwidth = 15.0f;
	float brd = brdx + (dim*brdwidth) + brdx + dim;
	float topleftX = (brd - (brickwidth * float(nBricksAcross))) / 2.0f;

	FrameTimer ft;
	Ball ball;
	RectF walls;
	Brick brick[nBricks];
	Paddle pad;
	Obstacle obstacle[nObstacles];
	Sound soundpad;
	Sound soundbrick;
	Sound soundobstacle;
	Sound soundgameover;
	Sound soundObstacle;
	Beveler bvl;

	std::mt19937 rng;
	bool GameOver = false;
	bool GameStart = false;
	int x = 0; int i = 0;
	int lives = 30;
	Brick brk;
	
	

	/********************************/
};