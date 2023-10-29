#pragma once

#include "Vec2.h"

class RectF
{
public:
	RectF() = default;
	RectF( float left_in,float right_in,float top_in,float bottom_in );
	RectF( const Vec2& topLeft,const Vec2& bottomRight );
	RectF( const Vec2& topLeft,float width,float height );
	bool IsOverlappingWith( const RectF& other ) const;
	bool IsContainedBy( const RectF& other);
	static RectF FromCenter(const Vec2& centre, float halfwidth, float halfheight);
	RectF GetExpanded(float offset) const;
	Vec2 GetCenter();
public:
	float left;
	float right;
	float top;
	float bottom;
};