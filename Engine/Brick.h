#pragma once

#include "RectF.h"
#include "Colors.h"
#include "Graphics.h"
#include "Ball.h"

class Brick
{
public:
	Brick( const RectF& rect_in,Color color_in );
	void Draw( Graphics& gfx ) const;
	bool IsBallColliding(Ball& ball);
private:
	RectF rect;
	Color color;
	bool destroyed = false;
};