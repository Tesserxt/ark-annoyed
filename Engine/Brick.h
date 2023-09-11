#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
public:
	Brick() = default;
	Brick( const RectF& rect_in,Color color_in );
	void Draw( Graphics& gfx ) const;
	bool IsBallColliding(Ball& ball );
	void ExecuteBallColliding(Ball& ball);
	RectF GetRect();
	Vec2 GetCenter();
private:
	Vec2 pos;
	static constexpr float padding = 1.0f;
	RectF rect;
	Color color;
	bool destroyed = false;
};