#include "Walls.h"
#include <assert.h>

Walls::Walls(const RectF& in_innerbounds, float in_thickness, Color baseColor)
	:
	innerbounds(in_innerbounds),
	thickness(in_thickness)
{
	bevel.SetBaseColor(baseColor);
	assert(innerbounds.GetExpanded(thickness).IsContainedBy(Graphics::GetScreenRect() )  );		
}

void Walls::Draw(Graphics& gfx) const
{
	bevel.DrawBevelFrame(innerbounds.GetExpanded(thickness*2.0f), int(thickness), gfx);
}

const RectF& Walls::GetInnerBounds() const
{
	return innerbounds;
}
