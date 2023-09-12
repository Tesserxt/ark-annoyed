#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Brick.h"
#include "RectF.h"

class Obstacle
{
public:
	Obstacle() = default;
	Obstacle(Vec2 in_pos, Vec2 in_vel);
	void Draw(Graphics& gfx);
	RectF GetRect();
	void Update(float dt);
	bool IsBallColliding(Ball& ball);
	bool IsWallColliding(RectF& walls);
	bool IsPadColliding(RectF& pad);
	void Rebound( float rate);
	bool destroyed = false;
private:
	Vec2 pos;
	Vec2 vel;
	float apothem = 10.0f;
};
