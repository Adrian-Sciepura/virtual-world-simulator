#define _CRT_SECURE_NO_WARNINGS
#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <cstdlib>
#include "../Graphics/Color.h"
#include "../Graphics/RGBColor.h"
#include "../Graphics/BMPFile.h"

class Utility
{
private:
	static RGBColor consoleColorsAsRGB[16];

public:
	static int random(int min, int max);
	static BMPFile* readBMP(const char* path);
	static Color convertRGBtoColor(const RGBColor& color);
};

#endif