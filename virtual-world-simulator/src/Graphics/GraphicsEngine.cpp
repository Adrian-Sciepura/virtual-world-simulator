#include "GraphicsEngine.h"

GraphicsEngine::GraphicsEngine(int screenWidth, int screenHeight) :
	screenWidth{ screenWidth }, screenHeight{ screenHeight }, numberOfChars{ screenWidth * screenHeight }, bytesWritten{ 0 }
{
	this->screenBuffer = new wchar_t[numberOfChars];
	this->console = GetStdHandle(STD_OUTPUT_HANDLE);
	this->font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
	init();
}

GraphicsEngine::~GraphicsEngine()
{
	delete[] screenBuffer;
}

void GraphicsEngine::init()
{
	setFont(8, 8, 700);
	setWindowSize(screenWidth, screenHeight);
	changeCursorVisibility(false);
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
	font.FontWeight = weight;
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

void GraphicsEngine::draw()
{
	WriteConsoleOutputCharacter(console, screenBuffer, numberOfChars, { 0,0 }, &bytesWritten);
}
