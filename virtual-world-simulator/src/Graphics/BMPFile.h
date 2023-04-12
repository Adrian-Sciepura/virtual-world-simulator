#ifndef BMP_FILE_H
#define BMP_FILE_H

#include "Color.h"

struct BMPFile
{
	int width;
	int height;
	Color* pixels;

	BMPFile(int width, int height);
	~BMPFile();
};

#endif