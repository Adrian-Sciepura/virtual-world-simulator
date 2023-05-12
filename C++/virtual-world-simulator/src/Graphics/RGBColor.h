#ifndef RGB_COLOR_H
#define RGB_COLOR_H

struct RGBColor
{
	int r;
	int g;
	int b;

	RGBColor(int r, int g, int b);
	bool operator==(const RGBColor& color) const;
};

#endif