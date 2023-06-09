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

bool Point::operator==(const Point& point) const
{
    if(this->x == point.x && this->y == point.y)
		return true;
	else
		return false;
}

std::ostream& operator<<(std::ostream& os, const Point& point)
{
    os << '[' << point.y << ", " << point.x << ']';
    return os;
}

std::istream& operator>>(std::istream& is, Point& point)
{
    is >> point.x >> point.y;
    return is;
}
