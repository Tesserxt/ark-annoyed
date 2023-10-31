#pragma once
#include "Vec2.h"
#include "RectF.h"
#include "Graphics.h"
#include "SpriteCodex.h"
#include <random>

class Ball
{
public:
	Ball(Vec2& in_pos, Vec2& in_dir);
	void Update( float dt );
	void Draw( Graphics& gfx );
	bool IsColliding( const RectF& walls);
	void ReboundX();
	void SetvelX();
	void ReboundY();
	bool isGameOver( const RectF& walls, int& lives);
	RectF GetRect();
	Vec2 GetVel();
	Vec2 GetPos();
	void SetDirection(Vec2& dir);
private:
	static constexpr float radius = 7.0f;
	static constexpr float speed  = 400.0f;
	Vec2 pos;
	Vec2 vel;
	std::mt19937 rng;
	std::uniform_real_distribution<float> xDist;

};
