﻿#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine(int screenWidth, int screenHeight) :
	screenWidth{ screenWidth }, screenHeight{ screenHeight }, numberOfChars{ screenWidth * screenHeight }, bytesWritten{ 0 }
{
	this->screenBuffer = new wchar_t[numberOfChars];
	this->screenColorsBuffer = new WORD[numberOfChars];
	this->console = GetStdHandle(STD_OUTPUT_HANDLE);
	this->font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	init();
}

GraphicsEngine::~GraphicsEngine()
{
	delete[] screenBuffer;
	delete[] screenColorsBuffer;
}

void GraphicsEngine::init()
{
	setFont(3, 3, 700);
	setWindowSize(screenWidth, screenHeight);
	changeCursorVisibility(false);
	for (int i = 0; i < numberOfChars; i++)
	{
		screenBuffer[i] = L'█';
		screenColorsBuffer[i] = Color::BLACK;
	}
	WriteConsoleOutputCharacter(console, screenBuffer, numberOfChars, { 0,0 }, &bytesWritten);
}

void GraphicsEngine::setWindowSize(int width, int height)
{
	COORD size = { width, height };
	SMALL_RECT rect1 = { 0, 0, 1, 1 };
	SMALL_RECT rect2 = { 0, 0, width - 1, height - 1 };

	SetConsoleWindowInfo(console, TRUE, &rect1);
	SetConsoleScreenBufferSize(console, size);
	SetConsoleWindowInfo(console, TRUE, &rect2);
}

void GraphicsEngine::setFont(int width, int height, int weight)
{
	GetCurrentConsoleFontEx(console, 0, &font);
	font.FontWeight = FW_NORMAL;
	font.FontFamily = FF_DONTCARE;
	font.dwFontSize.X = width;
	font.dwFontSize.Y = height;
	SetCurrentConsoleFontEx(console, NULL, &font);
}

void GraphicsEngine::changeCursorVisibility(bool visible)
{
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.dwSize = 100;
	cursorInfo.bVisible = visible;
	SetConsoleCursorInfo(console, &cursorInfo);
}

void GraphicsEngine::recolor(Color newColor, const Point& start, const Point& end)
{
	for(int i = start.y; i < end.y; i++)
		for (int j = start.x; j < end.x; j++)
			if (screenColorsBuffer[i * screenWidth + j] != Color::BLACK)
				screenColorsBuffer[i * screenWidth + j] = newColor;
}

void GraphicsEngine::drawBMP(BMPFile* image, const Point& position)
{
	int pos = 0;
	for (int i = 0; i < image->height; i++)
		for (int j = 0; j < image->width; j++)
		{
			if (position.x + j > screenWidth)
				continue;
			
			pos = (position.y + i) * screenWidth + position.x + j;
			if (pos > numberOfChars)
				break;

			screenColorsBuffer[pos] = image->pixels[i * image->width + j];
		}
}

void GraphicsEngine::drawBMPChunk(BMPFile* image, const Point& position, const Point& start, const Point& end)
{
	int pos = 0;
	for (int i = start.y; i < end.y; i++)
		for (int j = start.x; j < end.x; j++)
		{
			if (position.x + j - start.x > screenWidth)
				continue;

			pos = (position.y + i - start.y) * screenWidth + position.x + j - start.x;
			if (pos > numberOfChars)
				break;

			screenColorsBuffer[pos] = image->pixels[i * image->width + j];
		}
}

void GraphicsEngine::drawText(BMPFile* font, const std::string& text, const Point& position, Color color)
{
	const int lineSpacing = 2;
	int currentCharASCII = 0;
	int row = 0;
	int column = 0;
	int line = 0;
	int letter = 0;

	for (int i = 0; i < text.length(); i++)
	{
		if (text[i] == '\n')
		{
			line++;
			letter = 0;
			continue;
		}

		currentCharASCII = (int)text[i];
		row = currentCharASCII / 16;
		column = currentCharASCII % 16;

		drawBMPChunk(font, { position.x + letter * 8, position.y + line * (8 + lineSpacing) }, { column * 8, row * 8 }, { (column + 1) * 8, (row + 1) * 8 });
		letter++;
	}

	if (color != Color::NONE)
		recolor(color, position, { position.x + letter * 8, position.y + (line + 1) * 8 });
}

void GraphicsEngine::drawBuffer()
{
	WriteConsoleOutputAttribute(console, screenColorsBuffer, numberOfChars, { 0,0 }, &bytesWritten);
}

void GraphicsEngine::clearBuffer()
{
	for (int i = 0; i < numberOfChars; i++)
		screenColorsBuffer[i] = Color::BLACK;
}

wchar_t* GraphicsEngine::getScreenBuffer()
{
	return this->screenBuffer;
}

WORD* GraphicsEngine::getScreenColorsBuffer()
{
	return this->screenColorsBuffer;
}

int GraphicsEngine::getScreenWidth() const
{
	return this->screenWidth;
}

int GraphicsEngine::getScreenHeight() const
{
	return this->screenHeight;
}
