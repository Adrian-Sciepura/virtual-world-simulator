#include "BMPFile.h"

BMPFile::BMPFile(int width, int height) :
	width{ width }, height{ height }, pixels{ new Color[width * height] }
{
}

BMPFile::~BMPFile()
{
	delete[] pixels;
}
