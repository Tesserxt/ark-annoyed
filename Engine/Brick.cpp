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
	return SideFirstCollided(ball);
}

bool Brick::SideFirstCollided(Ball& ball)
{
	RectF ballrect = ball.GetRect();
	bool horizontal = rect.top <= ballrect.top && rect.bottom >= ballrect.bottom;
	
	if ( horizontal && !destroyed && rect.IsOverlappingWith(ballrect)) //for x
	{
		ball.ReboundX();
		destroyed = true;
		return true;	
	}

	bool vertical = rect.left <= ballrect.left && rect.right >= ballrect.right;

	if ( vertical && !destroyed && rect.IsOverlappingWith(ballrect)) //for y
	{
		ball.ReboundY();
		destroyed = true;
		return true;
	}
	return false;

}

RectF Brick::GetRect()
{
	return rect;
}
