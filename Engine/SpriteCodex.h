#pragma once

#include "Graphics.h"
#include "Vec2.h"

class SpriteCodex
{
public:
	// centered drawing of 14x14 sprite
	static void DrawBall(const Vec2& center, Graphics& gfx);
	static void DrawGameOver(const Vec2& center, Graphics& gfx);
	static void DrawPoo(const Vec2& center, Graphics& gfx);
	static void DrawFace(const Vec2& center, Graphics& gfx);
	static void DrawPooBoard(const int x, const int width, Graphics& gfx);
	static void DrawTitleScreen(int x, int y, Graphics& gfx);
};