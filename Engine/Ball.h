#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include <random>

class Ball
{
public:
	Ball(Vec2& in_pos, Vec2& in_vel);
	void Update( float dt );
	void Draw( Graphics& gfx );
	bool IsColliding(RectF& walls);
	void ReboundX();
	void SetvelX();
	void ReboundY();
	RectF GetRect();
	Vec2 GetVel();
	Vec2 GetPos();
private:
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist;

};
