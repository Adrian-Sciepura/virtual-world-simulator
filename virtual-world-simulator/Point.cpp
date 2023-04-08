#include "Point.h"

Point::Point() : x{0}, y{0}
{
}

Point::Point(int x, int y) : x{x}, y{y}
{
}

Point::Point(const Point& point) : x{point.x}, y{point.y}
{
}

int Point::getX()
{
    return this->x;
}

int Point::getY()
{
    return this->y;
}

Point& Point::operator=(const Point& point)
{
    this->x = point.x;
    this->y = point.y;
    return *this;
}

Point& Point::operator+(const Point& point)
{
    this->x += point.x;
    this->y += point.y;
    return *this;
}

Point& Point::operator-(const Point& point)
{
    this->x -= point.x;
    this->y -= point.y;
    return *this;
}

bool Point::operator==(const Point& point)
{
    if(this->x == point.x && this->y == point.y)
		return true;
	else
		return false;
}
