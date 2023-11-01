#include "Beveler.h"

void Beveler::DrawOuterBevel(const RectF& rect, int size, Graphics& gfx) const
{
	const int left	  = int(rect.left );
	const int right	  = int(rect.right );
	const int top	  = int(rect.top );
	const int bottom  = int(rect.bottom );

	//Bevel left
	gfx.DrawIsoRightTriBL(left, top, size, leftcolor);
	gfx.DrawRect(left, top + size, left + size, bottom - size, leftcolor);
	gfx.DrawIsoRightTriUL(left, bottom - size, size, leftcolor);

	//Bevel right
	gfx.DrawIsoRightTriBR(right - size, top, size, rightcolor);
	gfx.DrawRect(right - size, top + size, right, bottom - size, rightcolor);
	gfx.DrawIsoRightTriUR( right - size, bottom - size, size, rightcolor);

	//Bevel top
	gfx.DrawIsoRightTriUR(left, top, size, topcolor);
	gfx.DrawRect(left + size, top, right - size, top + size, topcolor);
	gfx.DrawIsoRightTriUL(right-size, top, size, topcolor);

	//Bevel bottom
	gfx.DrawIsoRightTriBR(left, bottom - size, size, bottomcolor);
	gfx.DrawRect(left + size, bottom - size, right - size, bottom, bottomcolor);
	gfx.DrawIsoRightTriBL(right - size, bottom - size, size, bottomcolor);

}

void Beveler::DrawInnerBevel(const RectF& rect, int size, Graphics& gfx) const
{
	const int left   = int(rect.left);
	const int right  = int(rect.right);
	const int top    = int(rect.top);
	const int bottom = int(rect.bottom);
	// left side bevel (corner,side,corner)
	gfx.DrawIsoRightTriBL(left, top, size, rightcolor);
	gfx.DrawRect(left, top + size, left + size, bottom - size, rightcolor);
	gfx.DrawIsoRightTriUL(left, bottom - size, size, rightcolor);
	// top side bevel
	gfx.DrawIsoRightTriUR(left, top, size, bottomcolor);
	gfx.DrawRect(left + size, top, right - size, top + size, bottomcolor);
	gfx.DrawIsoRightTriUL(right - size, top, size, bottomcolor);
	// right side bevel
	gfx.DrawIsoRightTriBR(right - size, top, size, leftcolor);
	gfx.DrawRect(right - size, top + size, right, bottom - size, leftcolor);
	gfx.DrawIsoRightTriUR(right - size, bottom - size, size, leftcolor);
	// bottom side bevel
	gfx.DrawIsoRightTriBR(left, bottom - size, size, topcolor);
	gfx.DrawRect(left + size, bottom - size, right - size, bottom, topcolor);
	gfx.DrawIsoRightTriBL(right - size, bottom - size, size, topcolor);
}

void Beveler::SetBaseColor(Color in_base)
{
	baseColor = in_base;
	topcolor = Color(
		int(  float(baseColor.GetR() ) * topfactor),
		int(  float(baseColor.GetG() ) * topfactor),
		int(  float(baseColor.GetB() ) * topfactor) );

	bottomcolor = Color(
		int(float(baseColor.GetR()) * bottomfactor),
		int(float(baseColor.GetG()) * bottomfactor),
		int(float(baseColor.GetB()) * bottomfactor) );

	rightcolor = Color(
		int(float(baseColor.GetR()) * rightfactor),
		int(float(baseColor.GetG()) * rightfactor),
		int(float(baseColor.GetB()) * rightfactor));

	leftcolor = Color(
		int(float(baseColor.GetR()) * leftfactor),
		int(float(baseColor.GetG()) * leftfactor),
		int(float(baseColor.GetB()) * leftfactor));
}

void Beveler::DrawBeveledBrick(RectF& rect, int bevelsize, Graphics& gfx)
{
	DrawInnerBevel(rect, bevelsize, gfx);
	gfx.DrawRect(rect.GetExpanded( -bevelsize ), baseColor);
}

void Beveler::DrawBevelFrame(const RectF& rect, int bevelSize, Graphics& gfx) const
{
	DrawOuterBevel(rect, bevelSize, gfx);
	DrawInnerBevel(rect.GetExpanded(-float(bevelSize)), bevelSize, gfx);
}

Color Beveler::GetBaseColor() const
{
	return baseColor;
}

