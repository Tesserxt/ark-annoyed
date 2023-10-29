#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"
#include "Beveler.h"

class Brick
{
public:
	Brick() = default;
	Brick( const RectF& rect_in,Color color_in );
	void Draw( Graphics& gfx );
	bool IsBallColliding(Ball& ball );
	void ExecuteBallColliding(Ball& ball);
	RectF GetRect();
	Vec2 GetCenter();
private:
	Vec2 pos;
	static constexpr float padding = 1.5f;
	static constexpr int bevelsize = 4;
	RectF rect;
	Color color;
	Beveler bevel;
	bool destroyed = false;
};