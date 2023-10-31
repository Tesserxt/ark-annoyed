#include "Walls.h"

Walls::Walls(const RectF& in_innerbounds, float in_thickness, Color baseColor)
	:
	innerbounds(in_innerbounds),
	thickness(in_thickness)
{
	bevel.SetBaseColor(baseColor);
}

void Walls::Draw(Graphics& gfx) const
{
	bevel.DrawBevelFrame(innerbounds, thickness, gfx);
}

const RectF& Walls::GetInnerBounds() const
{
	return innerbounds;
}
