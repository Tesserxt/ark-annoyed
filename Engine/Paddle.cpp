#include "Paddle.h"
#include <iostream>
Paddle::Paddle(Vec2& in_pos, float in_halfwidth, float in_halfheight)
	:
	pos(in_pos),
	halfwidth(in_halfwidth),
	halfheight(in_halfheight),
	exitXfactor(maxExitRatio / halfwidth),
	fixedZoneHalfwidth(fixedZoneWidthRatio* halfwidth),
	fixedZoneExitX(exitXfactor * fixedZoneHalfwidth)
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

bool Paddle::IsBallColliding(Ball& ball)
{
	if (!cooldown && GetRect().IsOverlappingWith(ball.GetRect()))
	{
		if (std::signbit(ball.GetVel().x) == std::signbit(ball.GetPos().x - pos.x) ||
			ball.GetPos().x <= GetRect().right && ball.GetPos().x >= GetRect().left)
		{
			ball.ReboundY();
			const float xdiff = ball.GetPos().x - pos.x;

			Vec2 dir;
			if (std::abs(xdiff) < fixedZoneHalfwidth)
			{
				if (xdiff < 0.0f)
				{
					dir = Vec2( -fixedZoneExitX, -1.0f );
				}
				else
				{
					dir = Vec2( fixedZoneExitX,  -1.0f );
				}
			}
			else
			{
				dir = Vec2( xdiff * 0.0045, -1.0f );
			}
			
			ball.SetDirection( dir );
		}
		else
		{
			ball.ReboundX();
		}
		cooldown = true;
		return true;
	}
	return false;
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, halfwidth, halfheight);
}

Vec2 Paddle::GetPos()
{
	return pos;
}

void Paddle::ResetCoolDown()
{
	cooldown = false;
}
