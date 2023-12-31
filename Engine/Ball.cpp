#include "Ball.h"

Ball::Ball(Vec2& in_pos, Vec2& in_vel)
	:
	pos(in_pos),
	vel(in_vel)
{
}

void Ball::Update(float dt)
{
	pos += vel * dt;
}

void Ball::Draw(Graphics& gfx)
{
	SpriteCodex::DrawBall(pos, gfx);
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

RectF Ball::GetRect()
{
	return RectF::FromCenter( pos, radius, radius);
}

Vec2 Ball::GetVel()
{
	return vel;
}

Vec2 Ball::GetPos()
{
	return pos;
}

bool Ball::IsColliding(RectF& walls)
{
	RectF ball = GetRect();
	bool collided = false;
	if( ball.left <= walls.left )
	{
		pos.x += walls.left - ball.left;
		ReboundX();
		collided = true;
	}
	if( ball.right >= walls.right )
	{
		pos.x += walls.right - ball.right;
		ReboundX();
		collided = true;
	}
	if( ball.top <= walls.top )
	{
		pos.y += walls.top - ball.top;
		ReboundY();
		collided = true;
	}
	if (ball.bottom >= walls.bottom)
	{
		pos.y += walls.bottom - ball.bottom;
		ReboundY();
		collided = true;
	}
	return collided;

	
}
