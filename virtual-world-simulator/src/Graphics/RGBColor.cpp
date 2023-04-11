#include "RGBColor.h"

RGBColor::RGBColor(int r, int g, int b) :
	r{ r }, g{ g }, b{ b }
{
}

bool RGBColor::operator==(const RGBColor& color) const
{
	return r == color.r && g == color.g && b == color.b;
}