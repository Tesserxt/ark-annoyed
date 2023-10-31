#pragma once

#include "RectF.h"
#include "Graphics.h"
#include "Beveler.h"

class Walls
{
public:
	Walls( const RectF& in_innerbounds, float in_thickness, Color baseColor ); 
	void Draw(Graphics& gfx) const;
    const RectF& GetInnerBounds() const;
private:
	RectF innerbounds;
	float thickness;
	Beveler bevel;
};
