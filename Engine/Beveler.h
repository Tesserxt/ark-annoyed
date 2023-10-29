#pragma once
#include "RectF.h"
#include "Graphics.h"

class Beveler
{
public:
	void DrawInnerBevel(const RectF& rect, int size, Graphics& gfx) const;
	void DrawOuterBevel(const RectF& rect, int size, Graphics& gfx) const;
	void SetBaseColor(Color in_base);
	void DrawBeveledBrick(RectF& rect, int bevelsize, Graphics& gfx);
	void DrawBevelFrame(const RectF& rect, int bevelSize, Graphics& gfx) const;
	Color GetBaseColor() const;

private:
	float rightfactor   = 0.65f;
	float leftfactor    = 1.10f;
	float topfactor		= 0.93f;
	float bottomfactor  = 0.80f;
	Color baseColor;
	Color rightcolor;
	Color leftcolor;
	Color topcolor;
	Color bottomcolor;

};