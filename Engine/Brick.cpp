#include "Brick.h"

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
	if (!destroyed && GetRect().IsOverlappingWith(ball.GetRect()))
	{
		if (std::signbit(ball.GetVel().x) == std::signbit(ball.GetPos().x - pos.x))
		{
			ball.ReboundY();
		}
		else if (ball.GetPos().x <= GetRect().right && ball.GetPos().x >= GetRect().left)
		{
			ball.ReboundY();
		}
		else if (ball.GetPos().y <= GetRect().top && ball.GetPos().y >= GetRect().bottom)
		{
			ball.ReboundX();
		}
		destroyed = true;
		return true;
	}
	return false;
}

RectF Brick::GetRect()
{
	return rect;
}
