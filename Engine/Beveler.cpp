#include "Beveler.h"

void Beveler::DrawInnerBevel(RectF& rect, int size, Graphics& gfx)
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

