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
	RectF ballrect = ball.GetRect();
	return SideFirstCollided(ball);
}

bool Brick::SideFirstCollided(Ball& ball)
{
	RectF ballrect = ball.GetRect();
	bool horizontal = rect.top <= ballrect.top && rect.bottom >= ballrect.bottom; //checking if hitted brick horizontally( either left or right side)
	
	if ( horizontal && !destroyed && rect.IsOverlappingWith(ballrect)) 
	{
		ball.ReboundX();
		destroyed = true;
		return true;	
	}
	else //checking if hitted brick vertically( either top or bottom)
	{
		ball.ReboundY();
		destroyed = true;
		return true;
	}
	return false;
}
