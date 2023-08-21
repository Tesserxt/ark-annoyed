#include "Paddle.h"

Paddle::Paddle( Vec2& in_pos, float in_halfwidth, float in_halfheight)
	:
	pos(in_pos),
	halfwidth(in_halfwidth),
	halfheight(in_halfheight)
{
}

void Paddle::Draw(Graphics& gfx) const
{
	RectF rect = GetRect();
	gfx.DrawRect( rect, c);
	rect.left += wing_width;
	rect.right -= wing_width;
	rect.bottom -= wing_width;
	gfx.DrawRect(rect, wing_color);
	
}

void Paddle::Update( const Keyboard& kbd, const float dt)
{
	if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += vel * dt ;
	}
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= vel * dt;
	}
}

void Paddle::IsWallColliding( const RectF& walls)
{
	RectF rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
	}
	else if (rect.right > walls.right)
	{
		pos.x += walls.right - rect.right;
	}	
}

bool Paddle::IsBallColliding(Ball& ball) const
{
	if ( ball.GetVel().y > 0.0f && GetRect().IsOverlappingWith(ball.GetRect()))
	{
		ball.ReboundY();
		return true;
	}
	return false;
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, halfwidth, halfheight);
}
