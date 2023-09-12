#include "Brick.h"
#include <assert.h>

Brick::Brick( const RectF & rect_in,Color color_in )
	:
	rect( rect_in ),
	color( color_in )
{
}

void Brick::Draw( Graphics & gfx ) const
{
	if (!destroyed)
	{
		gfx.DrawRect(rect.GetExpanded( -padding ), color);
	}
}

bool Brick::IsBallColliding(Ball& ball )
{
	return (!destroyed && GetRect().IsOverlappingWith(ball.GetRect()));
}

void Brick::ExecuteBallColliding(Ball& ball)
{
	assert( !destroyed && GetRect().IsOverlappingWith( ball.GetRect() ));

	if (std::signbit(ball.GetVel().x) == std::signbit(ball.GetPos().x - GetCenter().x) )
	{
		ball.ReboundY();
	}
	else if (ball.GetPos().x <= GetRect().right && ball.GetPos().x >= GetRect().left)
	{
		ball.ReboundY();
	}
	else
	{
		ball.ReboundX();
	}
	destroyed = true;
}

RectF Brick::GetRect()
{
	return rect;
}

Vec2 Brick::GetCenter()
{
	return rect.GetCenter();
}
