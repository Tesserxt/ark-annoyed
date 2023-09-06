#pragma once

#include "Graphics.h"
#include "Colors.h"
#include "Keyboard.h"
#include "Vec2.h"
#include "RectF.h"
#include "Ball.h"

class Paddle
{
public:
	Paddle(Vec2& in_pos, float in_halfwiidth, float in_halfheight);
	void Draw(Graphics& gfx) const;
	void Update( const Keyboard& kbd, const float dt);
	void IsWallColliding( const RectF& walls);
	bool IsBallColliding(Ball& ball);
	RectF GetRect() const;
	Vec2 GetPos();
	void Resetcooldown();
private:
	Color c = Colors::Gray;
	Color wing_color = Colors::Cyan;
	float wing_width = 7.0f;
	Vec2  pos;
	float vel = 300.0f;
	float halfwidth;
	float halfheight;
	bool cooldown = false; 

};
