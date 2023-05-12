#ifndef GRAPHICS_ENGINE_H
#define GRAPHICS_ENGINE_H

#include <stdlib.h>
#include <Windows.h>
#include "Color.h"
#include "BMPFile.h"
#include "../Common/Point.h"

class GraphicsEngine
{
private:
	int screenWidth;
	int screenHeight;
	int numberOfChars;

	wchar_t* screenBuffer;
	WORD* screenColorsBuffer;
	HANDLE console;
	DWORD bytesWritten;
	CONSOLE_FONT_INFOEX font;

	void init();

public:
	GraphicsEngine(int screenWidth, int screenHeight);
	~GraphicsEngine();

	void setWindowSize(int width, int height);
	void setFont(int width, int height, int weight);
	void changeCursorVisibility(bool visible);

	void recolor(Color newColor, const Point& start, const Point& end);
	void drawBMP(BMPFile* image, const Point& position);
	void drawBMPChunk(BMPFile* image, const Point& position, const Point& start, const Point& end);
	void drawText(BMPFile* font, const std::string& text, const Point& position, Color color = Color::NONE);
	void drawBuffer();
	void clearBuffer();

	wchar_t* getScreenBuffer();
	WORD* getScreenColorsBuffer();
	int getScreenWidth() const;
	int getScreenHeight() const;
};

#endif