#include "Obstacle.h"

Obstacle::Obstacle(Vec2 in_pos, Vec2 in_vel)
	:
	pos(in_pos),
	vel(in_vel)
{
}

void Obstacle::Draw(Graphics& gfx)
{
	if (!destroyed)
		SpriteCodex::DrawFace(pos, gfx);
}

RectF Obstacle::GetRect()
{
	return RectF::FromCenter(pos, apothem, apothem);
}

void Obstacle::Update(float dt)
{
	if(!destroyed)
		pos += vel * dt;
}

bool Obstacle::IsBallColliding(Ball& Ball)
{

	RectF face = GetRect();
	RectF ball = Ball.GetRect();
	if (!destroyed && GetRect().IsOverlappingWith(Ball.GetRect()));
	bool horizontal = face.top <= ball.top && face.bottom >= ball.bottom;
	
	if ( horizontal && !destroyed && ball.IsOverlappingWith( face )) //for x
	{
		Rebound(-1.1f);
		Ball.ReboundY();
		return true;	
	}

	bool vertical = face.left <= ball.left && face.right >= ball.right;

	if ( vertical && !destroyed && ball.IsOverlappingWith( face )) //for y
	{
		Rebound(-1.0f);
		Ball.ReboundX();
		return true;
	}
	return false;
}

bool Obstacle::IsWallColliding(RectF& walls)
{
	if (!destroyed)
	{
		RectF Face = GetRect();
		if (Face.left <= walls.left)
		{
			destroyed = true;
		}
		if (Face.right >= walls.right)
		{
			destroyed = true;
		}
		if (Face.top <= walls.top)
		{
			destroyed = true;
		}
		if (Face.bottom >= walls.bottom)
		{
			destroyed = true;
		}
		return destroyed;
	}
}

bool Obstacle::IsPadColliding(RectF& pad)
{
	return GetRect().IsOverlappingWith(pad);
}



void Obstacle::Rebound(float rate)
{
	vel.y = vel.y * rate;
}
