#include "Utility.h"

RGBColor Utility::consoleColorsAsRGB[16] = {
	RGBColor(12, 12, 12),
	RGBColor(0, 55, 218),
	RGBColor(19, 161, 14),
	RGBColor(58, 150, 221),
	RGBColor(197, 15, 31),
	RGBColor(136, 23, 152),
	RGBColor(193, 156, 0),
	RGBColor(204, 204, 204),
	RGBColor(118, 118, 118),
	RGBColor(59, 120, 255),
	RGBColor(22, 198, 12),
	RGBColor(97, 214, 214),
	RGBColor(231, 72, 86),
	RGBColor(180, 0, 158),
	RGBColor(249, 241, 165),
	RGBColor(242, 242, 242)
};

int Utility::random(int min, int max)
{
    return rand() % (max - min + 1) + min;
}

BMPFile* Utility::readBMP(const char* path)
{
    int i;
    FILE* f = fopen(path, "rb");

    if (f == NULL)
        return nullptr;

    unsigned char info[54];
    fread(info, sizeof(unsigned char), 54, f);

    int width = *(int*)&info[18];
    int height = *(int*)&info[22];
    int numOfPixels = width * height;
    BMPFile* bmpFile = new BMPFile(width, height);

    int row_padded = (width * 3 + 3) & (~3);
    unsigned char* data = new unsigned char[row_padded];
    unsigned char tmp;

    for (int i = 0; i < height; i++)
    {
        fread(data, sizeof(unsigned char), row_padded, f);
        for (int j = 0; j < width * 3; j += 3)
        {
            tmp = data[j];
            data[j] = data[j + 2];
            data[j + 2] = tmp;
            bmpFile->pixels[(height - i - 1) * width + j / 3] = convertRGBtoColor(RGBColor(data[j], data[j + 1], data[j + 2]));
        }
    }

    delete[] data;
    fclose(f);
    return bmpFile;
}

Color Utility::convertRGBtoColor(const RGBColor& color)
{
    for (int i = 0; i < 16; i++)
        if(color == consoleColorsAsRGB[i])
            return (Color)i;

    return Color::BLACK;
}
